/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Inc/Renderer.hpp"
#include "../Inc/DrawException.hpp"
#include "../Inc/Window.hpp"

using namespace GameEngine::Draw;
using namespace GameEngine::OS;

bool Renderer::Initialize(Window* window, DrawAPI api)
{
	bgfx::Init init;
	init.platformData.nwh = window->GetNativePtr();

	const vec2i wndSize = window->GetSize();
	init.resolution.width = wndSize.X;
	init.resolution.height = wndSize.Y;

	init.type = (bgfx::RendererType::Enum)api;

	if (!bgfx::init(init))
	{
		throw new DrawException("Failed intializing bgfx!");
		return false;
	}

#if _DEBUG
	bgfx::setDebug(BGFX_DEBUG_TEXT); // BGFX_DEBUG_WIREFRAME
#endif

	bgfx::setViewClear(0, BGFX_CLEAR_COLOR | BGFX_CLEAR_DEPTH);
	bgfx::reset(wndSize.X, wndSize.Y, BGFX_RESET_NONE);
	bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
	return true;
}

void Renderer::Release()
{
	bgfx::shutdown();
}

void Renderer::BeginDraw(Window* window, bool vsync, MSAA msaa)
{
	if (window->IsResized())
	{
		const vec2i wndSize = window->GetSize();
		bgfx::reset(wndSize.X, wndSize.Y, (vsync ? BGFX_RESET_VSYNC : BGFX_RESET_NONE) | (uint)msaa);
		bgfx::setViewRect(0, 0, 0, bgfx::BackbufferRatio::Equal);
	}

	bgfx::touch(0);

#if _DEBUG
	bgfx::dbgTextClear();
#endif
}

void Renderer::EndDraw()
{
	bgfx::frame();
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

bgfx::VertexBufferHandle Renderer::CreateVertexBuffer(const void* data, uint size, bgfx::VertexLayout& layout)
{
	return bgfx::createVertexBuffer(bgfx::copy(data, size), layout);
}

bgfx::IndexBufferHandle Renderer::CreateIndexBuffer(const void* data, uint size)
{
	return bgfx::createIndexBuffer(bgfx::copy(data, size));
}
