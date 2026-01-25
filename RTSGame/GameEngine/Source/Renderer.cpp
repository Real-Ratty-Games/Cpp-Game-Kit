/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Public/Renderer.hpp"
#include "../Public/Window.hpp"
#include "../Public/FileSystem.hpp"
#include "../Public/Shader.hpp"
#include "../Public/Sprite.hpp"
#include "../Public/DrawSurface.hpp"
#include "../Public/Transformation.hpp"
#include "../Public/Animation.hpp"
#include <bx/math.h>
#include <stdexcept>

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

using namespace GameEngine;

/// Active instances for sprite rendering
Shader*			_ActiveShader		= nullptr;
DrawSurface*	_ActiveDrawSurface	= nullptr;

/// For primitive 2D quad rendering
bgfx::VertexBufferHandle	_Quad2DVB;
float						_Quad2DView[16];

inline void Renderer_Init2DQuad();
inline void Renderer_Release2DQuad();
inline void Renderer_DrawTexture(Texture* texture, vec2& rotpiv, vec2& size, Transform2D& transformation);

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
		throw new std::runtime_error("Failed intializing bgfx!");
		return false;
	}

#if _DEBUG
	bgfx::setDebug(BGFX_DEBUG_TEXT); // BGFX_DEBUG_WIREFRAME
#endif

	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH);
	bgfx::reset(wndSize.X, wndSize.Y, (vsync ? BGFX_RESET_VSYNC : BGFX_RESET_NONE) | (uint)msaa);
	bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);

	Renderer_Init2DQuad();
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
		throw new std::runtime_error(errmsg);
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
		throw new std::runtime_error(errmsg);
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
		else throw new std::runtime_error("Failed loading texture from memory!");

		auto header = data.data();
		int height = *reinterpret_cast<cstrg>(header + 12);
		int width = *reinterpret_cast<cstrg>(header + 16);
		texture.Size = vec2i(width, height);
	}
	else throw new std::runtime_error("Failed loading texture from memory; Data was empty!");
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

void Renderer::BeginDrawSprite(DrawSurface* surface, Camera2D& cam)
{
	_ActiveDrawSurface = surface;

	_ActiveDrawSurface->Clear();

	float proj[16];
	bx::mtxOrtho(proj, cam.Location.X, cam.Size.X + cam.Location.Y,
		cam.Size.Y + cam.Location.Y, cam.Location.Y, 0.1f, 100.0f, 0.0f, false);
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

void Renderer::PrepareSpriteInstancing(Sprite* sprite, InstanceData& idata, std::vector<Transform2D>& tdata)
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
		mdl = Math::Translate(mdl, vec3(transf.Location.X, transf.Location.Y, 0.0f));					// move to world pos
		mdl = Math::Translate(mdl, rotPiv);																// mov pivot to origin
		mdl = Math::Rotate(mdl, vec3(0.0f, 0.0f, 1.0f), Math::ToRadians(transf.Rotation));				// rotate
		mdl = Math::Translate(mdl, -rotPiv);															// move pivot back
		mdl = Math::Scale(mdl, vec3(rscale.X, rscale.Y, 1.0f));											// scale


		const float* _mtx = mdl.Ptr();
		memcpy(data, _mtx, insStride);
		data += 64;

		vec4 color = vec4(transf.ImageColor.R, transf.ImageColor.G, transf.ImageColor.B, transf.ImageColor.A);
		memcpy(data, color.Ptr(), sizeof(vec4));
		data += sizeof(vec4);
	}
}

void Renderer::PrepareSpriteAtlasInstancing(Sprite* sprite, InstanceData& idata, std::vector<TransformAtlas2D>& tdata, vec2 subSize)
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
		mdl = Math::Translate(mdl, vec3(transf.Location.X, transf.Location.Y, 0.0f));				// move to world pos
		mdl = Math::Translate(mdl, rotPiv);															// mov pivot to origin
		mdl = Math::Rotate(mdl, vec3(0.0f, 0.0f, 1.0f), Math::ToRadians(transf.Rotation));			// rotate
		mdl = Math::Translate(mdl, -rotPiv);														// move pivot back
		mdl = Math::Scale(mdl, vec3(rscale.X, rscale.Y, 1.0f));										// scale

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

void Renderer::DrawSpriteInstanced(InstanceData& idata)
{
	SetState(BGFX_STATE_WRITE_RGB |
		BGFX_STATE_WRITE_A |
		BGFX_STATE_BLEND_ALPHA |
		BGFX_STATE_DEPTH_TEST_LESS);
	bgfx::setVertexBuffer(0, _Quad2DVB);
	bgfx::setInstanceDataBuffer(&idata.Buffer);
	_ActiveShader->SetTexture(0, "s_texColor", *idata.pSprite->GetTexture());
	_ActiveShader->Submit(_ActiveDrawSurface->ViewID(), true);
}

void Renderer::DrawSpriteAtlasInstanced(InstanceData& idata, Sprite* sprite, vec2 subSize)
{
	vec4 atinf[2];
	atinf[0] = vec4(0.0f, 0.0f, sprite->Size.X, sprite->Size.Y);
	atinf[1] = vec4(subSize.X, subSize.Y, 1.0f, 0.0f);
	_ActiveShader->SetUniform("atlasInfo", atinf, 2);
	DrawSpriteInstanced(idata);
}

void Renderer::PrepareSpriteFontText(Sprite* sprite, Transform2D& transformation, InstanceData& idata, vec2 subSize, strgv text)
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

		switch (it)
		{
		case 'A': result.Index = vec2(0, 0); break;
		case 'a': result.Index = vec2(1, 0); break;
		case 'B': result.Index = vec2(2, 0); break;
		case 'b': result.Index = vec2(3, 0); break;
		case 'C': result.Index = vec2(4, 0); break;
		case 'c': result.Index = vec2(5, 0); break;
		case 'D': result.Index = vec2(6, 0); break;
		case 'd': result.Index = vec2(7, 0); break;
		case 'E': result.Index = vec2(8, 0); break;
		case 'e': result.Index = vec2(9, 0); break;
		case 'F': result.Index = vec2(10, 0); break;
		case 'f': result.Index = vec2(11, 0); break;
		case 'G': result.Index = vec2(12, 0); break;
		case 'g': result.Index = vec2(13, 0); break;
		case 'H': result.Index = vec2(14, 0); break;
		case 'h': result.Index = vec2(15, 0); break;
		case 'I': result.Index = vec2(16, 0); break;
		case 'i': result.Index = vec2(17, 0); break;
		case 'J': result.Index = vec2(18, 0); break;
		case 'j': result.Index = vec2(19, 0); break;
		case 'K': result.Index = vec2(20, 0); break;
		case 'k': result.Index = vec2(21, 0); break;
		case 'L': result.Index = vec2(22, 0); break;
		case 'l': result.Index = vec2(23, 0); break;
		case 'M': result.Index = vec2(24, 0); break;
		case 'm': result.Index = vec2(25, 0); break;
		case 'N': result.Index = vec2(26, 0); break;
		case 'n': result.Index = vec2(27, 0); break;
		case 'O': result.Index = vec2(28, 0); break;
		case 'o': result.Index = vec2(29, 0); break;
		case 'P': result.Index = vec2(30, 0); break;
		case 'p': result.Index = vec2(31, 0); break;
		case 'Q': result.Index = vec2(32, 0); break;
		case 'q': result.Index = vec2(33, 0); break;
		case 'R': result.Index = vec2(34, 0); break;
		case 'r': result.Index = vec2(35, 0); break;
		case 'S': result.Index = vec2(36, 0); break;
		case 's': result.Index = vec2(37, 0); break;
		case 'T': result.Index = vec2(38, 0); break;
		case 't': result.Index = vec2(39, 0); break;
		case 'U': result.Index = vec2(40, 0); break;
		case 'u': result.Index = vec2(41, 0); break;
		case 'V': result.Index = vec2(42, 0); break;
		case 'v': result.Index = vec2(43, 0); break;
		case 'W': result.Index = vec2(44, 0); break;
		case 'w': result.Index = vec2(45, 0); break;
		case 'X': result.Index = vec2(46, 0); break;
		case 'x': result.Index = vec2(47, 0); break;
		case 'Y': result.Index = vec2(48, 0); break;
		case 'y': result.Index = vec2(49, 0); break;
		case 'Z': result.Index = vec2(50, 0); break;
		case 'z': result.Index = vec2(51, 0); break;
		case 'Ä': result.Index = vec2(52, 0); break;
		case 'ä': result.Index = vec2(53, 0); break;
		case 'Ö': result.Index = vec2(54, 0); break;
		case 'ö': result.Index = vec2(55, 0); break;
		case 'Ü': result.Index = vec2(56, 0); break;
		case 'ü': result.Index = vec2(57, 0); break;
		case '0': result.Index = vec2(58, 0); break;
		case '1': result.Index = vec2(59, 0); break;
		case '2': result.Index = vec2(60, 0); break;
		case '3': result.Index = vec2(61, 0); break;
		case '4': result.Index = vec2(62, 0); break;
		case '5': result.Index = vec2(63, 0); break;
		case '6': result.Index = vec2(64, 0); break;
		case '7': result.Index = vec2(65, 0); break;
		case '8': result.Index = vec2(66, 0); break;
		case '9': result.Index = vec2(67, 0); break;
		case ',': result.Index = vec2(68, 0); break;
		case ';': result.Index = vec2(69, 0); break;
		case '.': result.Index = vec2(70, 0); break;
		case ':': result.Index = vec2(71, 0); break;
		case '-': result.Index = vec2(72, 0); break;
		case '_': result.Index = vec2(73, 0); break;
		case '!': result.Index = vec2(74, 0); break;
		case '?': result.Index = vec2(75, 0); break;
		case '"': result.Index = vec2(76, 0); break;
		case '§': result.Index = vec2(77, 0); break;
		case '$': result.Index = vec2(78, 0); break;
		case '%': result.Index = vec2(79, 0); break;
		case '&': result.Index = vec2(80, 0); break;
		case '/': result.Index = vec2(81, 0); break;
		case '(': result.Index = vec2(82, 0); break;
		case ')': result.Index = vec2(83, 0); break;
		case '=': result.Index = vec2(84, 0); break;
		case '*': result.Index = vec2(85, 0); break;
		case '+': result.Index = vec2(86, 0); break;
		case '~': result.Index = vec2(87, 0); break;
		case '\'': result.Index = vec2(88, 0); break;
		case '#': result.Index = vec2(89, 0); break;
		case '|': result.Index = vec2(90, 0); break;
		case '<': result.Index = vec2(91, 0); break;
		case '>': result.Index = vec2(92, 0); break;
		case '²': result.Index = vec2(93, 0); break;
		case '³': result.Index = vec2(94, 0); break;
		case '{': result.Index = vec2(95, 0); break;
		case '[': result.Index = vec2(96, 0); break;
		case ']': result.Index = vec2(97, 0); break;
		case '}': result.Index = vec2(98, 0); break;
		case '\\': result.Index = vec2(99, 0); break;
		case ' ':
		{
			cursor.X += subSize.X;
			continue;
		}break;
		case '\n':
		{
			cursor.X = transformation.Location.X;
			cursor.Y += subSize.Y;
			continue;
		}break;
		}
		tdata.push_back(result);

		cursor.X += subSize.X;
	}

	PrepareSpriteAtlasInstancing(sprite, idata, tdata, subSize);
}

void Renderer::DrawSpriteFontText(Sprite* sprite, InstanceData& idata, vec2 subSize)
{
	DrawSpriteAtlasInstanced(idata, sprite, subSize);
}

void Renderer::DrawSpriteFontText(Sprite* sprite, Transform2D& transformation, vec2 subSize, strgv text)
{
	vec2 cursor = transformation.Location;
	for (auto& it : text)
	{
		TransformAtlas2D result;
		result.Location = cursor;
		result.Rotation = transformation.Rotation;
		result.Scale = transformation.Scale;
		result.ImageColor = transformation.ImageColor;

		switch (it)
		{
		case 'A': result.Index = vec2(0, 0); break;
		case 'a': result.Index = vec2(1, 0); break;
		case 'B': result.Index = vec2(2, 0); break;
		case 'b': result.Index = vec2(3, 0); break;
		case 'C': result.Index = vec2(4, 0); break;
		case 'c': result.Index = vec2(5, 0); break;
		case 'D': result.Index = vec2(6, 0); break;
		case 'd': result.Index = vec2(7, 0); break;
		case 'E': result.Index = vec2(8, 0); break;
		case 'e': result.Index = vec2(9, 0); break;
		case 'F': result.Index = vec2(10, 0); break;
		case 'f': result.Index = vec2(11, 0); break;
		case 'G': result.Index = vec2(12, 0); break;
		case 'g': result.Index = vec2(13, 0); break;
		case 'H': result.Index = vec2(14, 0); break;
		case 'h': result.Index = vec2(15, 0); break;
		case 'I': result.Index = vec2(16, 0); break;
		case 'i': result.Index = vec2(17, 0); break;
		case 'J': result.Index = vec2(18, 0); break;
		case 'j': result.Index = vec2(19, 0); break;
		case 'K': result.Index = vec2(20, 0); break;
		case 'k': result.Index = vec2(21, 0); break;
		case 'L': result.Index = vec2(22, 0); break;
		case 'l': result.Index = vec2(23, 0); break;
		case 'M': result.Index = vec2(24, 0); break;
		case 'm': result.Index = vec2(25, 0); break;
		case 'N': result.Index = vec2(26, 0); break;
		case 'n': result.Index = vec2(27, 0); break;
		case 'O': result.Index = vec2(28, 0); break;
		case 'o': result.Index = vec2(29, 0); break;
		case 'P': result.Index = vec2(30, 0); break;
		case 'p': result.Index = vec2(31, 0); break;
		case 'Q': result.Index = vec2(32, 0); break;
		case 'q': result.Index = vec2(33, 0); break;
		case 'R': result.Index = vec2(34, 0); break;
		case 'r': result.Index = vec2(35, 0); break;
		case 'S': result.Index = vec2(36, 0); break;
		case 's': result.Index = vec2(37, 0); break;
		case 'T': result.Index = vec2(38, 0); break;
		case 't': result.Index = vec2(39, 0); break;
		case 'U': result.Index = vec2(40, 0); break;
		case 'u': result.Index = vec2(41, 0); break;
		case 'V': result.Index = vec2(42, 0); break;
		case 'v': result.Index = vec2(43, 0); break;
		case 'W': result.Index = vec2(44, 0); break;
		case 'w': result.Index = vec2(45, 0); break;
		case 'X': result.Index = vec2(46, 0); break;
		case 'x': result.Index = vec2(47, 0); break;
		case 'Y': result.Index = vec2(48, 0); break;
		case 'y': result.Index = vec2(49, 0); break;
		case 'Z': result.Index = vec2(50, 0); break;
		case 'z': result.Index = vec2(51, 0); break;
		case 'Ä': result.Index = vec2(52, 0); break;
		case 'ä': result.Index = vec2(53, 0); break;
		case 'Ö': result.Index = vec2(54, 0); break;
		case 'ö': result.Index = vec2(55, 0); break;
		case 'Ü': result.Index = vec2(56, 0); break;
		case 'ü': result.Index = vec2(57, 0); break;
		case '0': result.Index = vec2(58, 0); break;
		case '1': result.Index = vec2(59, 0); break;
		case '2': result.Index = vec2(60, 0); break;
		case '3': result.Index = vec2(61, 0); break;
		case '4': result.Index = vec2(62, 0); break;
		case '5': result.Index = vec2(63, 0); break;
		case '6': result.Index = vec2(64, 0); break;
		case '7': result.Index = vec2(65, 0); break;
		case '8': result.Index = vec2(66, 0); break;
		case '9': result.Index = vec2(67, 0); break;
		case ',': result.Index = vec2(68, 0); break;
		case ';': result.Index = vec2(69, 0); break;
		case '.': result.Index = vec2(70, 0); break;
		case ':': result.Index = vec2(71, 0); break;
		case '-': result.Index = vec2(72, 0); break;
		case '_': result.Index = vec2(73, 0); break;
		case '!': result.Index = vec2(74, 0); break;
		case '?': result.Index = vec2(75, 0); break;
		case '"': result.Index = vec2(76, 0); break;
		case '§': result.Index = vec2(77, 0); break;
		case '$': result.Index = vec2(78, 0); break;
		case '%': result.Index = vec2(79, 0); break;
		case '&': result.Index = vec2(80, 0); break;
		case '/': result.Index = vec2(81, 0); break;
		case '(': result.Index = vec2(82, 0); break;
		case ')': result.Index = vec2(83, 0); break;
		case '=': result.Index = vec2(84, 0); break;
		case '*': result.Index = vec2(85, 0); break;
		case '+': result.Index = vec2(86, 0); break;
		case '~': result.Index = vec2(87, 0); break;
		case '\'': result.Index = vec2(88, 0); break;
		case '#': result.Index = vec2(89, 0); break;
		case '|': result.Index = vec2(90, 0); break;
		case '<': result.Index = vec2(91, 0); break;
		case '>': result.Index = vec2(92, 0); break;
		case '²': result.Index = vec2(93, 0); break;
		case '³': result.Index = vec2(94, 0); break;
		case '{': result.Index = vec2(95, 0); break;
		case '[': result.Index = vec2(96, 0); break;
		case ']': result.Index = vec2(97, 0); break;
		case '}': result.Index = vec2(98, 0); break;
		case '\\': result.Index = vec2(99, 0); break;
		case ' ':
		{
			cursor.X += subSize.X;
			continue;
		}break;
		case '\n':
		{
			cursor.X = transformation.Location.X;
			cursor.Y += subSize.Y;
			continue;
		}break;
		}
		
		DrawSpriteAtlas(sprite, result, subSize);

		cursor.X += subSize.X;
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

/*======================================================
======================================================*/

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
	mdl = Math::Translate(mdl, vec3(transformation.Location.X, transformation.Location.Y, 0.0f));		// move to world pos
	mdl = Math::Translate(mdl, rotPiv);																	// mov pivot to origin
	mdl = Math::Rotate(mdl, vec3(0.0f, 0.0f, 1.0f), Math::ToRadians(transformation.Rotation));			// rotate
	mdl = Math::Translate(mdl, -rotPiv);																// move pivot back
	mdl = Math::Scale(mdl, vec3(rscale.X, rscale.Y, 1.0f));												// scale

	bgfx::setTransform(mdl.Ptr());
	Renderer::SetState(BGFX_STATE_WRITE_RGB |
		BGFX_STATE_WRITE_A |
		BGFX_STATE_BLEND_ALPHA |
		BGFX_STATE_DEPTH_TEST_LESS);

	vec4 ucolor = vec4(transformation.ImageColor.R, transformation.ImageColor.G, transformation.ImageColor.B, transformation.ImageColor.A);
	_ActiveShader->SetUniform("color", ucolor.Ptr());

	bgfx::setVertexBuffer(0, _Quad2DVB);
	_ActiveShader->SetTexture(0, "s_texColor", *texture);
	_ActiveShader->Submit(_ActiveDrawSurface->ViewID(), true);
}
