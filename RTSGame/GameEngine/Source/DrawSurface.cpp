/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Public/DrawSurface.hpp"
#include <bx/bx.h>

using namespace GameEngine;

DrawSurface::DrawSurface(uint16 viewid, void* wndHandle)
{
	Location		= vec2i(0);
	Resolution		= vec2(1280.0f, 720.0f);
	AspectRatio		= vec2(16.0f, 9.0f);
	ClearColor		= 0xfff;
	bTopMost		= true;
	bTransparent	= false;

	mViewId = viewid;
	pWindowHandle = wndHandle;

	bgfx::setViewMode(mViewId, bgfx::ViewMode::Sequential);

	mFbHandle = BGFX_INVALID_HANDLE;
	if (viewid != 0)
	{
		vec2i rs = vec2i(static_cast<int>(Resolution.X), static_cast<int>(Resolution.Y));
		UpdateFB(rs);
		SetFBViewId();
	}

	bgfx::setViewRect(mViewId, Location.X, Location.Y, static_cast<uint16>(Resolution.X), static_cast<uint16>(Resolution.Y));
	bgfx::setViewScissor(mViewId, Location.X, Location.Y, static_cast<uint16>(Resolution.X), static_cast<uint16>(Resolution.Y));

	uint16 flags = BGFX_CLEAR_NONE;
	if (bTopMost)
		flags |= BGFX_CLEAR_DEPTH;
	if (!bTransparent)
		flags |= BGFX_CLEAR_COLOR;
	bgfx::setViewClear(mViewId, flags, ClearColor, 1.0f, 0);
}

void DrawSurface::Release()
{
	if(mViewId != 0)
		DestroyFB();
}

void DrawSurface::Clear()
{
	uint16 flags = BGFX_CLEAR_NONE;
	if (bTopMost)
		flags |= BGFX_CLEAR_DEPTH;
	if (!bTransparent)
		flags |= BGFX_CLEAR_COLOR;

	bgfx::setViewClear(mViewId, flags, ClearColor, 1.0f, 0);
}

void DrawSurface::OnResize(vec2 size)
{
	Resolution = size;
	AspectRatio = Resolution;

	if (bgfx::isValid(mFbHandle))
	{
		DestroyFB();
		vec2i rs = vec2i(static_cast<int>(Resolution.X), static_cast<int>(Resolution.Y));
		UpdateFB(rs);
		SetFBViewId();
	}

	bgfx::setViewRect(mViewId, Location.X, Location.Y, static_cast<uint16>(Resolution.X), static_cast<uint16>(Resolution.Y));
	bgfx::setViewScissor(mViewId, Location.X, Location.Y, static_cast<uint16>(Resolution.X), static_cast<uint16>(Resolution.Y));
}

uint16 DrawSurface::ViewID() const
{
	return mViewId;
}

Texture& DrawSurface::GetTexture()
{
	return mFbTex;
}

void DrawSurface::DestroyFB()
{
	if (bgfx::isValid(mFbHandle))
	{
		bgfx::destroy(mFbHandle);
		mFbHandle.idx = bgfx::kInvalidHandle;
		bgfx::setViewFrameBuffer(mViewId, BGFX_INVALID_HANDLE);
	}
}

void DrawSurface::SetFBViewId()
{
	bgfx::setViewFrameBuffer(mViewId, mFbHandle);
}

void DrawSurface::UpdateFB(vec2i texSize, bgfx::TextureFormat::Enum format)
{
	if (!bgfx::isValid(mFbHandle))
	{
		if (pWindowHandle != nullptr)
			mFbHandle = bgfx::createFrameBuffer(pWindowHandle, texSize.X, texSize.Y, format, bgfx::TextureFormat::D32F);
		else
		{
			mFbTex.Handle = bgfx::createTexture2D(
				(uint16)texSize.X
				, (uint16)texSize.Y
				, false
				, 1
				, format
				, BGFX_TEXTURE_RT
			);

			mFbTex.Size = texSize;
			mFbHandle = bgfx::createFrameBuffer(1, &mFbTex.Handle, true);
		}
	}
}
