/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef RENDERER_HPP_
#define RENDERER_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include "DrawData.hpp"

using namespace GameEngine::Core;

namespace GameEngine
{
	namespace OS
	{
		class Window;
	}

	namespace Draw::Renderer
	{
		GAMEENGINEAPI inline bool Initialize(OS::Window* window, DrawAPI api);
		GAMEENGINEAPI inline void Release();
		GAMEENGINEAPI inline void BeginDraw(OS::Window* window, bool vsync, MSAA msaa);
		GAMEENGINEAPI inline void EndDraw();

		GAMEENGINEAPI const bgfx::Caps* GetGPUInfo();
		GAMEENGINEAPI inline void Printf(vec2i location, uint8 attr, strgv text);

		GAMEENGINEAPI inline void SetScissor(vec2i location, vec2i size);

		GAMEENGINEAPI inline bgfx::VertexBufferHandle CreateVertexBuffer(const void* data, uint size, bgfx::VertexLayout& layout);
		GAMEENGINEAPI inline bgfx::IndexBufferHandle CreateIndexBuffer(const void* data, uint size);
	}
}
#endif