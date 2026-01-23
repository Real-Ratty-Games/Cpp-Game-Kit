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
	class DrawSurface;
	class SpriteAnimator;

	namespace Renderer
	{
		GAMEENGINEAPI inline bool Initialize(Window* window, DrawAPI api, bool vsync, MSAA msaa);
		GAMEENGINEAPI inline void Release();
		GAMEENGINEAPI inline void BeginDraw();
		GAMEENGINEAPI inline void EndDraw();

		GAMEENGINEAPI inline void OnResize(vec2i size, bool vsync, MSAA msaa);

		GAMEENGINEAPI const bgfx::Caps* GetGPUInfo();
		GAMEENGINEAPI inline void Printf(vec2i location, uint8 attr, strgv text);

		GAMEENGINEAPI inline void SetScissor(vec2i location, vec2i size);
		GAMEENGINEAPI inline void SetViewScissor(uint16 viewid, vec2i location, vec2i size);

		GAMEENGINEAPI inline void SetState(uint64 state);

		GAMEENGINEAPI inline bgfx::VertexBufferHandle CreateVertexBuffer(const void* data, uint size, bgfx::VertexLayout& layout);
		GAMEENGINEAPI inline bgfx::IndexBufferHandle CreateIndexBuffer(const void* data, uint size);

		GAMEENGINEAPI void LoadTextureFromFile(Texture& texture, strgv filename, uint64 flags, strgv texturename, bool flipUV);
		GAMEENGINEAPI void LoadTextureFromMemory(Texture& texture, std::vector<uint8>& data, uint64 flags, strgv texturename);
		GAMEENGINEAPI inline void FreeTexture(Texture& tex);

		GAMEENGINEAPI void SetActiveShader(Shader* shader);
		GAMEENGINEAPI void BeginDrawSprite(DrawSurface* surface, Camera2D& cam);
		GAMEENGINEAPI void DrawSprite(Sprite* sprite, Transform2D& transformation);
		GAMEENGINEAPI void DrawSpriteAtlas(Sprite* sprite, TransformAtlas2D& transformation, vec2 subSize);

		GAMEENGINEAPI void PrepareSpriteInstancing(Sprite* sprite, InstanceData& idata, std::vector<Transform2D>& tdata);
		GAMEENGINEAPI void PrepareSpriteAtlasInstancing(Sprite* sprite, InstanceData& idata, std::vector<TransformAtlas2D>& tdata, vec2 subSize);
			
		GAMEENGINEAPI void DrawSpriteInstanced(InstanceData& idata);
		GAMEENGINEAPI void DrawSpriteAtlasInstanced(InstanceData& idata, Sprite* sprite, vec2 subSize);

		GAMEENGINEAPI void PrepareSpriteFontText(Sprite* sprite, Transform2D& transformation, InstanceData& idata, vec2 subSize, strgv text);
		GAMEENGINEAPI void DrawSpriteFontText(Sprite* sprite, InstanceData& idata, vec2 subSize);
		GAMEENGINEAPI void DrawSpriteFontText(Sprite* sprite, Transform2D& transformation, vec2 subSize, strgv text);

		GAMEENGINEAPI void DrawSpriteAnimation(Sprite* sprite, Transform2D& transformation, SpriteAnimator* animator);
	}
}
#endif