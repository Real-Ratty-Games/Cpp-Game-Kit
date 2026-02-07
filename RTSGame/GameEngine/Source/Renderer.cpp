/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Include/Renderer.hpp"
#include "../Include/BigError.hpp"
#include "../Include/Window.hpp"
#include "../Include/FileSystem.hpp"
#include "../Include/Shader.hpp"
#include "../Include/Sprite.hpp"
#include "../Include/Viewport3D.hpp"
#include "../Include/DrawSurface.hpp"
#include "../Include/DrawSurface3D.hpp"
#include "../Include/Transformation.hpp"
#include "../Include/SpriteAnimation.hpp"
#include "../Include/Math.hpp"
#include <bx/math.h>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <unordered_set>
#include <fstream>
#include <sstream>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace GameEngine;

static struct RawMeshData
{
	std::vector<MeshVertex>	Vertices;
	std::vector<uint16>		Indices;
};

/// Active instances for rendering
static Shader*		_ActiveShader		= nullptr;
static DrawSurface*	_ActiveDrawSurface	= nullptr;

static bgfx::VertexLayout		_Mesh3DVBLayout;

/// For primitive 2D quad rendering
static bgfx::VertexBufferHandle	_Quad2DVB;
static float					_Quad2DView[16];

static void	Renderer_Init3DLayout();
static void	Renderer_Init2DQuad();
static void	Renderer_Release2DQuad();
static void	Renderer_DrawTexture(Texture* texture, vec2& rotpiv, vec2& size, Transform2D& transformation);
static void	Renderer_ModelProcessNode(Model3D& model, aiNode* node, const aiScene* scene);
static void	Renderer_ModelProcessMesh(Mesh3D& modelMesh, aiMesh* mesh, const aiScene* scene);
static void	Renderer_CreateMesh(Mesh3D& modelMesh, RawMeshData& mdata);

bool Renderer::Initialize(Window* window, DrawAPI api, bool vsync, MSAA msaa)
{
	bgfx::Init init;
	init.platformData.nwh = window->GetNativePtr();

	const vec2i wndSize = window->GetSize();
	init.resolution.width = wndSize.X;
	init.resolution.height = wndSize.Y;

	init.type = (bgfx::RendererType::Enum)api;

	if (!bgfx::init(init))
	{
		throw BigError("Failed intializing bgfx!");
		return false;
	}

#if _DEBUG
	bgfx::setDebug(BGFX_DEBUG_TEXT); // BGFX_DEBUG_WIREFRAME
#endif

	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH);
	bgfx::reset(wndSize.X, wndSize.Y, (vsync ? BGFX_RESET_VSYNC : BGFX_RESET_NONE) | (uint)msaa);
	bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

	Renderer_Init2DQuad();
	Renderer_Init3DLayout();
	return true;
}

void Renderer::Release()
{
	Renderer_Release2DQuad();
	bgfx::shutdown();
}

void Renderer::BeginDraw()
{
	bgfx::touch(0);

#if _DEBUG
	bgfx::dbgTextClear();
#endif
}

void Renderer::EndDraw()
{
	bgfx::frame();
}

void Renderer::OnResize(vec2i size, bool vsync, MSAA msaa)
{
	bgfx::reset(size.X, size.Y, (vsync ? BGFX_RESET_VSYNC : BGFX_RESET_NONE) | (uint)msaa);
}

const bgfx::Caps* Renderer::GetGPUInfo()
{
	return bgfx::getCaps();
}

void Renderer::Printf(vec2i location, uint8 attr, strgv text)
{
#if _DEBUG
	bgfx::dbgTextPrintf(location.X, location.Y, attr, text.data());
#endif
}

void Renderer::SetScissor(vec2i location, vec2i size)
{
	bgfx::setScissor(location.X, location.Y, size.X, size.Y);
}

void Renderer::SetViewScissor(uint16 viewid, vec2i location, vec2i size)
{
	bgfx::setViewScissor(viewid, location.X, location.Y, size.X, size.Y);
}

void Renderer::SetState(uint64 state)
{
	bgfx::setState(state);
}

bgfx::VertexBufferHandle Renderer::CreateVertexBuffer(const void* data, uint size, bgfx::VertexLayout& layout)
{
	return bgfx::createVertexBuffer(bgfx::copy(data, size), layout);
}

bgfx::IndexBufferHandle Renderer::CreateIndexBuffer(const void* data, uint size)
{
	return bgfx::createIndexBuffer(bgfx::copy(data, size));
}

void Renderer::LoadTextureFromFile(Texture& texture, strgv filename, uint64 flags, strgv texturename, bool flipUV)
{
	stbi_set_flip_vertically_on_load(flipUV);
	int width, height, nrComponents;
	uint8* data = stbi_load(filename.data(), &width, &height, &nrComponents, 0);

	if (!data)
	{
		const strg errmsg = "Failed loading texture from file: " + strg(filename);
		throw BigError(errmsg);
	}

	unsigned char* out = data;
	bgfx::TextureFormat::Enum format = bgfx::TextureFormat::R8;
	if (nrComponents == 3)
		format = bgfx::TextureFormat::RGB8;
	else if (nrComponents == 4)
		format = bgfx::TextureFormat::RGBA8;

	texture.Handle = bgfx::createTexture2D(
		static_cast<uint16>(width),
		static_cast<uint16>(height),
		false,
		0,
		format,
		flags,
		bgfx::copy(out, width * height * nrComponents));

	if (bgfx::isValid(texture.Handle))
		bgfx::setName(texture.Handle, texturename.data());
	else
	{
		const strg errmsg = "Failed loading texture from file: " + strg(filename);
		throw BigError(errmsg);
	}

	texture.Size = vec2i(width, height);

	stbi_image_free(out);
	stbi_set_flip_vertically_on_load(false);
}

void Renderer::LoadTextureFromMemory(Texture& texture, std::vector<uint8>& data, uint64 flags, strgv texturename)
{
	if (!data.empty())
	{
		texture.Handle = bgfx::createTexture(bgfx::copy(data.data(), data.size()), flags);

		if (bgfx::isValid(texture.Handle))
			bgfx::setName(texture.Handle, texturename.data());
		else
		{
			const strg errmsg = "Failed loading texture from memory: " + strg(texturename);
			throw BigError(errmsg);
		}

		auto header = data.data();
		int height = *reinterpret_cast<const char*>(header + 12);
		int width = *reinterpret_cast<const char*>(header + 16);
		texture.Size = vec2i(width, height);
	}
	else
	{
		const strg errmsg = "Failed loading texture from memory; Data was empty: " + strg(texturename);
		throw BigError(errmsg);
	}
}

void Renderer::FreeTexture(Texture& tex)
{
	if (bgfx::isValid(tex.Handle))
	{
		bgfx::destroy(tex.Handle);
		tex.Handle = BGFX_INVALID_HANDLE;
	}
}

void Renderer::SetActiveShader(Shader* shader)
{
	_ActiveShader = shader;
}

void Renderer::BeginDrawSprite(DrawSurface* surface, Viewport2D& viewport)
{
	_ActiveDrawSurface = surface;
	_ActiveDrawSurface->Clear();

	float proj[16];
	bx::mtxOrtho(proj, viewport.Location.X, viewport.Size.X + viewport.Location.Y,
		viewport.Size.Y + viewport.Location.Y, viewport.Location.Y, 0.1f, 100.0f, 0.0f, false);
	bgfx::setViewTransform(_ActiveDrawSurface->ViewID(), _Quad2DView, proj);
}

void Renderer::DrawSprite(Sprite* sprite, Transform2D& transformation)
{
	Renderer_DrawTexture(sprite->GetTexture(), sprite->RotationPivot, sprite->Size, transformation);
}

void Renderer::DrawSpriteAtlas(Sprite* sprite, TransformAtlas2D& transformation, vec2 subSize)
{
	vec4 atinf[2];
	atinf[0] = vec4(transformation.Index.X, transformation.Index.Y, sprite->Size.X, sprite->Size.Y);
	atinf[1] = vec4(subSize.X, subSize.Y, 1.0f, 0.0f);
	_ActiveShader->SetUniform("atlasInfo", atinf, 2);
	Renderer_DrawTexture(sprite->GetTexture(), sprite->RotationPivot, subSize, transformation);
}

void Renderer::PrepareSpriteInstancing(Sprite* sprite, SpriteInstanceData& idata, std::vector<Transform2D>& tdata)
{
	const int insCnt = tdata.size();
	const uint16 insStride = 64 + sizeof(vec4);
	uint drawnIns = bgfx::getAvailInstanceDataBuffer(insCnt, insStride);

	idata.MissedAmount = insCnt - drawnIns;
	idata.pSprite = sprite;

	bgfx::allocInstanceDataBuffer(&idata.Buffer, drawnIns, insStride);

	uint8* data = idata.Buffer.data;

	for (uint i = 0; i < drawnIns; i++)
	{
		auto& transf = tdata[i];
		vec2 rscale = sprite->Size * transf.Scale;

		vec3 rotPiv = vec3(
			sprite->RotationPivot.X * rscale.X,
			sprite->RotationPivot.Y * rscale.Y,
			0.0f
		);

		mat4 mdl = mat4::Identity();
		mdl = Math::Translate(mdl, vec3(transf.Location.X, transf.Location.Y, 0.0f), false);					// move to world pos
		mdl = Math::Translate(mdl, rotPiv, false);																// mov pivot to origin
		mdl = Math::Rotate(mdl, vec3(0.0f, 0.0f, 1.0f), Math::ToRadians(transf.Rotation), false);				// rotate
		mdl = Math::Translate(mdl, -rotPiv, false);																// move pivot back
		mdl = Math::Scale(mdl, vec3(rscale.X, rscale.Y, 1.0f), false);											// scale


		const float* _mtx = mdl.Ptr();
		memcpy(data, _mtx, insStride);
		data += 64;

		vec4 color = vec4(transf.ImageColor.R, transf.ImageColor.G, transf.ImageColor.B, transf.ImageColor.A);
		memcpy(data, color.Ptr(), sizeof(vec4));
		data += sizeof(vec4);
	}
}

void Renderer::PrepareSpriteAtlasInstancing(Sprite* sprite, SpriteInstanceData& idata, std::vector<TransformAtlas2D>& tdata, vec2 subSize)
{
	const int insCnt = tdata.size();
	const uint16 insStride = 64 + sizeof(vec4);
	uint drawnIns = bgfx::getAvailInstanceDataBuffer(insCnt, insStride);

	idata.MissedAmount = insCnt - drawnIns;
	idata.pSprite = sprite;

	bgfx::allocInstanceDataBuffer(&idata.Buffer, drawnIns, insStride);

	uint8* data = idata.Buffer.data;

	for (uint i = 0; i < drawnIns; i++)
	{
		auto& transf = tdata[i];
		vec2 rscale = subSize * transf.Scale;

		vec3 rotPiv = vec3(
			sprite->RotationPivot.X * rscale.X,
			sprite->RotationPivot.Y * rscale.Y,
			0.0f
		);

		mat4 mdl = mat4::Identity();
		mdl = Math::Translate(mdl, vec3(transf.Location.X, transf.Location.Y, 0.0f), false);				// move to world pos
		mdl = Math::Translate(mdl, rotPiv, false);															// mov pivot to origin
		mdl = Math::Rotate(mdl, vec3(0.0f, 0.0f, 1.0f), Math::ToRadians(transf.Rotation), false);			// rotate
		mdl = Math::Translate(mdl, -rotPiv, false);															// move pivot back
		mdl = Math::Scale(mdl, vec3(rscale.X, rscale.Y, 1.0f), false);										// scale

		// sneak in blue value in unused z value
		vec4& csp = *((vec4*)(&mdl.Data[0]));
		csp.Z = transf.ImageColor.B;

		// sneak in alpha value in unused z value
		vec4& csp2 = *((vec4*)(&mdl.Data[4]));
		csp2.Z = transf.ImageColor.A;

		const float* _mtx = mdl.Ptr();
		memcpy(data, _mtx, insStride);
		data += 64;

		vec4 color = vec4(transf.Index.X, transf.Index.Y, transf.ImageColor.R, transf.ImageColor.G);
		memcpy(data, color.Ptr(), sizeof(vec4));
		data += sizeof(vec4);
	}
}

void Renderer::DrawSpriteInstanced(SpriteInstanceData& idata)
{
	SetState(BGFX_STATE_WRITE_RGB |
		BGFX_STATE_WRITE_A |
		BGFX_STATE_BLEND_ALPHA |
		BGFX_STATE_DEPTH_TEST_LESS);
	bgfx::setVertexBuffer(0, _Quad2DVB);
	bgfx::setInstanceDataBuffer(&idata.Buffer);
	_ActiveShader->SetTexture(0, "s_texColor", *idata.pSprite->GetTexture());
	_ActiveShader->Submit(_ActiveDrawSurface->ViewID(), 0, true);
}

void Renderer::DrawSpriteAtlasInstanced(SpriteInstanceData& idata, Sprite* sprite, vec2 subSize)
{
	vec4 atinf[2];
	atinf[0] = vec4(0.0f, 0.0f, sprite->Size.X, sprite->Size.Y);
	atinf[1] = vec4(subSize.X, subSize.Y, 1.0f, 0.0f);
	_ActiveShader->SetUniform("atlasInfo", atinf, 2);
	DrawSpriteInstanced(idata);
}

void Renderer::PrepareSpriteFontText(SpriteFont& font, Transform2D& transformation, SpriteInstanceData& idata, strgv text)
{
	std::vector<TransformAtlas2D> tdata;

	vec2 cursor = transformation.Location;
	for (auto& it : text)
	{
		TransformAtlas2D result;
		result.Location = cursor;
		result.Rotation = transformation.Rotation;
		result.Scale = transformation.Scale;
		result.ImageColor = transformation.ImageColor;

		if (it == ' ')
		{
			cursor.X += font.GlyphSize.X;
			continue;
		}
		else if (it == '\n')
		{
			cursor.X = transformation.Location.X;
			cursor.Y += font.GlyphSize.Y;
			continue;
		}

		auto pos = font.Glyphs.find(it);
		if (pos != strg::npos)
			result.Index.X = static_cast<int>(pos);
		else continue;

		tdata.push_back(result);

		cursor.X += font.GlyphSize.X;
	}

	PrepareSpriteAtlasInstancing(font.pSprite, idata, tdata, font.GlyphSize);
}

void Renderer::DrawSpriteFontText(SpriteFont& font, SpriteInstanceData& idata)
{
	DrawSpriteAtlasInstanced(idata, font.pSprite, font.GlyphSize);
}

void Renderer::DrawSpriteFontText(SpriteFont& font, Transform2D& transformation, strgv text)
{
	vec2 cursor = transformation.Location;
	for (auto& it : text)
	{
		TransformAtlas2D result;
		result.Location = cursor;
		result.Rotation = transformation.Rotation;
		result.Scale = transformation.Scale;
		result.ImageColor = transformation.ImageColor;

		if (it == ' ')
		{
			cursor.X += font.GlyphSize.X;
			continue;
		}
		else if (it == '\n')
		{
			cursor.X = transformation.Location.X;
			cursor.Y += font.GlyphSize.Y;
			continue;
		}

		auto pos = font.Glyphs.find(it);
		if (pos != strg::npos)
			result.Index.X = static_cast<int>(pos);
		else continue;
		
		DrawSpriteAtlas(font.pSprite, result, font.GlyphSize);

		cursor.X += font.GlyphSize.X;
	}
}

void Renderer::DrawSpriteAnimation(Sprite* sprite, Transform2D& transformation, SpriteAnimator* animator)
{
	TransformAtlas2D transf;
	transf.Location		= transformation.Location;
	transf.Rotation		= transformation.Rotation;
	transf.Scale		= transformation.Scale;
	transf.ImageColor	= transformation.ImageColor;
	transf.Index		= animator->GetCurrentIndex();
	DrawSpriteAtlas(sprite, transf, animator->GetAnimation()->FrameSize);
}

void Renderer::LoadModelFromFile(Model3D& model, strgv filename)
{
	if (!FileSystem::Exists(filename))
	{
		const strg errmsg = "Model file could not be found: " + strg(filename);
		throw BigError(errmsg);
	}

	Assimp::Importer importer;
	uint flags = aiProcess_FlipUVs
		| aiProcess_Triangulate
		| aiProcess_GenSmoothNormals
		| aiProcess_CalcTangentSpace
		| aiProcess_SplitLargeMeshes
		| aiProcess_OptimizeMeshes;

	const aiScene* scene = importer.ReadFile(filename.data(), flags);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
	{
		{
			const strg errmsg = "Failed loading model: " + strg(filename);
			throw BigError(errmsg);
		}
	}

	Renderer_ModelProcessNode(model, scene->mRootNode, scene);
}

void Renderer::LoadModelFromMemory(Model3D& model, std::vector<uint8>& data)
{
	Assimp::Importer importer;
	uint flags = aiProcess_FlipUVs
		| aiProcess_Triangulate
		| aiProcess_GenSmoothNormals
		| aiProcess_CalcTangentSpace
		| aiProcess_SplitLargeMeshes
		| aiProcess_OptimizeMeshes;

	const aiScene* scene = importer.ReadFileFromMemory(data.data(), data.size(), flags);

	if (!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
		throw BigError("Failed loading model!");

	Renderer_ModelProcessNode(model, scene->mRootNode, scene);
}

void Renderer::BeginDraw3D(DrawSurface3D* surface, Viewport3D& viewport)
{
	_ActiveDrawSurface = surface;
	_ActiveDrawSurface->Clear();

	float proj[16];
	bx::mtxProj(proj, viewport.Fov, surface->AspectRatio.X / surface->AspectRatio.Y, viewport.Near, viewport.Far,
		bgfx::getCaps()->homogeneousDepth);
	bgfx::setViewTransform(surface->ViewID(), viewport.View().Ptr(), proj);
}

void Renderer::BeginDraw3D(DrawSurface3D* surface, ViewportOrtho3D& viewport)
{
	_ActiveDrawSurface = surface;
	_ActiveDrawSurface->Clear();

	float proj[16];
	bx::mtxOrtho(proj, viewport.Left, viewport.Right, viewport.Bottom, viewport.Top, viewport.Near,
		viewport.Far, viewport.Offset, true);
	bgfx::setViewTransform(surface->ViewID(), viewport.View().Ptr(), proj);
}

/*======================================================
======================================================*/

void Renderer_Init3DLayout()
{
	_Mesh3DVBLayout.begin()
		.add(bgfx::Attrib::Position, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Normal, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Tangent, 3, bgfx::AttribType::Float)
		.add(bgfx::Attrib::Bitangent, 3, bgfx::AttribType::Float)
		.end();
}

void Renderer_Init2DQuad()
{
	static QuadVertex quadVertices[] = {
		{0.0f, 1.0f, 0.0f, 1.0f},
		{1.0f, 0.0f, 1.0f, 0.0f},
		{0.0f, 0.0f, 0.0f, 0.0f},
		{0.0f, 1.0f, 0.0f, 1.0f},
		{1.0f, 1.0f, 1.0f, 1.0f},
		{1.0f, 0.0f, 1.0f, 0.0f}
	};

	bgfx::VertexLayout pcvLayout;
	pcvLayout.begin()
		.add(bgfx::Attrib::Position, 2, bgfx::AttribType::Float)
		.add(bgfx::Attrib::TexCoord0, 2, bgfx::AttribType::Float)
		.end();

	_Quad2DVB = Renderer::CreateVertexBuffer(quadVertices, sizeof(quadVertices), pcvLayout);

	const bx::Vec3 at = { 0.0f, 0.0f,  0.0f };
	const bx::Vec3 eye = { 0.0f, 0.0f, -5.0f };
	bx::mtxLookAt(_Quad2DView, eye, at);
}

void Renderer_Release2DQuad()
{
	if (bgfx::isValid(_Quad2DVB))
	{
		bgfx::destroy(_Quad2DVB);
		_Quad2DVB = BGFX_INVALID_HANDLE;
	}
}

void Renderer_DrawTexture(Texture* texture, vec2& rotpiv, vec2& size, Transform2D& transformation)
{
	vec2 rscale = size * transformation.Scale;

	vec3 rotPiv = vec3(
		rotpiv.X * rscale.X,
		rotpiv.Y * rscale.Y,
		0.0f
	);

	mat4 mdl = mat4::Identity();
	mdl = Math::Translate(mdl, vec3(transformation.Location.X, transformation.Location.Y, 0.0f), false);		// move to world pos
	mdl = Math::Translate(mdl, rotPiv, false);																	// mov pivot to origin
	mdl = Math::Rotate(mdl, vec3(0.0f, 0.0f, 1.0f), Math::ToRadians(transformation.Rotation), false);			// rotate
	mdl = Math::Translate(mdl, -rotPiv, false);																	// move pivot back
	mdl = Math::Scale(mdl, vec3(rscale.X, rscale.Y, 1.0f), false);												// scale

	bgfx::setTransform(mdl.Ptr());
	Renderer::SetState(BGFX_STATE_WRITE_RGB |
		BGFX_STATE_WRITE_A |
		BGFX_STATE_BLEND_ALPHA |
		BGFX_STATE_DEPTH_TEST_LESS);

	vec4 ucolor = vec4(transformation.ImageColor.R, transformation.ImageColor.G, transformation.ImageColor.B, transformation.ImageColor.A);
	_ActiveShader->SetUniform("color", ucolor.Ptr());

	bgfx::setVertexBuffer(0, _Quad2DVB);

	_ActiveShader->SetTexture(0, "s_texColor", *texture);
	_ActiveShader->Submit(_ActiveDrawSurface->ViewID(), 0, true);
}

void Renderer_ModelProcessNode(Model3D& model, aiNode* node, const aiScene* scene)
{
	for (uint i = 0; i < node->mNumMeshes; i++)
	{
		aiMesh* mesh = scene->mMeshes[node->mMeshes[i]];
		model.Meshes.push_back(Mesh3D());
		Renderer_ModelProcessMesh(model.Meshes[model.Meshes.size()-1], mesh, scene);
	}

	for (uint i = 0; i < node->mNumChildren; i++)
		Renderer_ModelProcessNode(model, node->mChildren[i], scene);
}

void Renderer_ModelProcessMesh(Mesh3D& modelMesh, aiMesh* mesh, const aiScene* scene)
{
	RawMeshData result;
	result.Vertices.resize(mesh->mNumVertices);

	for (uint i = 0; i < mesh->mNumVertices; i++)
	{
		MeshVertex& vertex = result.Vertices[i];

		vertex.X = mesh->mVertices[i].x;
		vertex.Y = mesh->mVertices[i].y;
		vertex.Z = mesh->mVertices[i].z;

		if (mesh->HasNormals())
		{
			vertex.NX = mesh->mNormals[i].x;
			vertex.NY = mesh->mNormals[i].y;
			vertex.NZ = mesh->mNormals[i].z;
		}

		if (mesh->HasTextureCoords(0))
		{
			vertex.U = mesh->mTextureCoords[0][i].x;
			vertex.V = mesh->mTextureCoords[0][i].y;
		}

		if (mesh->HasTangentsAndBitangents())
		{
			vertex.TX = mesh->mTangents[i].x;
			vertex.TY = mesh->mTangents[i].y;
			vertex.TZ = mesh->mTangents[i].z;

			vertex.BX = mesh->mBitangents[i].x;
			vertex.BY = mesh->mBitangents[i].y;
			vertex.BZ = mesh->mBitangents[i].z;
		}
	}

	for (uint i = 0; i < mesh->mNumFaces; i++)
	{
		aiFace face = mesh->mFaces[i];
		for (uint j = 0; j < face.mNumIndices; j++)
			result.Indices.push_back(face.mIndices[j]);
	}

	Renderer_CreateMesh(modelMesh, result);
}

void Renderer_CreateMesh(Mesh3D& modelMesh, RawMeshData& mdata)
{
	modelMesh.VBH = Renderer::CreateVertexBuffer(mdata.Vertices.data(), mdata.Vertices.size() * sizeof(MeshVertex), _Mesh3DVBLayout);
	if (!bgfx::isValid(modelMesh.VBH))
		throw BigError("Vertex Buffer is invalid!");

	modelMesh.IBH = Renderer::CreateIndexBuffer(mdata.Indices.data(), mdata.Indices.size() * sizeof(uint16));
	if (!bgfx::isValid(modelMesh.IBH))
		throw BigError("Index Buffer is invalid!");
}
