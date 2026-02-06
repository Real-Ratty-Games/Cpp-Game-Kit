/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef RENDERER_HPP_
#define RENDERER_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include "DrawData.hpp"
#include <vector>

namespace GameEngine
{
	class Window;
	class Shader;
	class Sprite;
	class Viewport3D;
	class DrawSurface;
	class DrawSurface3D;
	class SpriteAnimator;
	class ViewportOrtho3D;

	namespace Renderer
	{
		GAMEENGINEAPI bool Initialize(Window* window, DrawAPI api, bool vsync, MSAA msaa);
		GAMEENGINEAPI void Release();
		GAMEENGINEAPI void BeginDraw();
		GAMEENGINEAPI void EndDraw();

		GAMEENGINEAPI void OnResize(vec2i size, bool vsync, MSAA msaa);

		GAMEENGINEAPI const bgfx::Caps* GetGPUInfo();

		/// 0x0f
		GAMEENGINEAPI void Printf(vec2i location, uint8 attr, strgv text);

		GAMEENGINEAPI void SetScissor(vec2i location, vec2i size);
		GAMEENGINEAPI void SetViewScissor(uint16 viewid, vec2i location, vec2i size);

		GAMEENGINEAPI void SetState(uint64 state);

		GAMEENGINEAPI bgfx::VertexBufferHandle CreateVertexBuffer(const void* data, uint size, bgfx::VertexLayout& layout);
		GAMEENGINEAPI bgfx::IndexBufferHandle CreateIndexBuffer(const void* data, uint size);

		GAMEENGINEAPI void LoadTextureFromFile(Texture& texture, strgv filename, uint64 flags, strgv texturename, bool flipUV);
		GAMEENGINEAPI void LoadTextureFromMemory(Texture& texture, std::vector<uint8>& data, uint64 flags, strgv texturename);
		GAMEENGINEAPI void FreeTexture(Texture& tex);

		GAMEENGINEAPI void SetActiveShader(Shader* shader);

		// Begin Sprite Rendering

		GAMEENGINEAPI void BeginDrawSprite(DrawSurface* surface, Viewport2D& viewport);
		GAMEENGINEAPI void DrawSprite(Sprite* sprite, Transform2D& transformation);
		GAMEENGINEAPI void DrawSpriteAtlas(Sprite* sprite, TransformAtlas2D& transformation, vec2 subSize);

		GAMEENGINEAPI void PrepareSpriteInstancing(Sprite* sprite, SpriteInstanceData& idata, std::vector<Transform2D>& tdata);
		GAMEENGINEAPI void PrepareSpriteAtlasInstancing(Sprite* sprite, SpriteInstanceData& idata, std::vector<TransformAtlas2D>& tdata, vec2 subSize);
			
		GAMEENGINEAPI void DrawSpriteInstanced(SpriteInstanceData& idata);
		GAMEENGINEAPI void DrawSpriteAtlasInstanced(SpriteInstanceData& idata, Sprite* sprite, vec2 subSize);

		GAMEENGINEAPI void PrepareSpriteFontText(SpriteFont& font, Transform2D& transformation, SpriteInstanceData& idata, strgv text);
		GAMEENGINEAPI void DrawSpriteFontText(SpriteFont& font, SpriteInstanceData& idata);
		GAMEENGINEAPI void DrawSpriteFontText(SpriteFont& font, Transform2D& transformation, strgv text);

		GAMEENGINEAPI void DrawSpriteAnimation(Sprite* sprite, Transform2D& transformation, SpriteAnimator* animator);

		// End Sprite Rendering

		GAMEENGINEAPI void LoadModelFromFile(Model3D& model, strgv filename);
		GAMEENGINEAPI void LoadModelFromMemory(Model3D& model, std::vector<uint8>& data);

		// Begin 3D Rendering

		GAMEENGINEAPI void BeginDraw3D(DrawSurface3D* surface, Viewport3D& viewport);
		GAMEENGINEAPI void BeginDraw3D(DrawSurface3D* surface, ViewportOrtho3D& viewport);

		// End 3D Rendering
	}
}
#endif