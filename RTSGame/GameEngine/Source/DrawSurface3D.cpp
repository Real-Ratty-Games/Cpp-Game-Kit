/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Include/DrawSurface3D.hpp"
#include <bx/bx.h>
#include <bx/math.h>

using namespace GameEngine;

DrawSurface3D::DrawSurface3D(uint16 viewid, void* wndHandle) : DrawSurface(viewid, wndHandle) {}

Texture& DrawSurface3D::GetDepthTexture()
{
	return mFbDepthTex;
}

void DrawSurface3D::UpdateFB(vec2i texSize, bgfx::TextureFormat::Enum format)
{
	if (!bgfx::isValid(mFbHandle))
	{
		if (pWindowHandle != nullptr)
			mFbHandle = bgfx::createFrameBuffer(pWindowHandle, texSize.X, texSize.Y, format, bgfx::TextureFormat::D32F);
		else
		{
			bgfx::TextureHandle fbtextures[] =
			{
				bgfx::createTexture2D(
					(uint16)texSize.X
					, (uint16)texSize.Y
					, false
					, 1
					, format
					, BGFX_TEXTURE_RT
				),

				bgfx::createTexture2D(
					(uint16)texSize.X
					, (uint16)texSize.Y
					, false
					, 1
					, bgfx::TextureFormat::D32F
					, BGFX_TEXTURE_RT | BGFX_SAMPLER_COMPARE_LEQUAL
				)
			};

			mFbTex.Handle		= fbtextures[0];
			mFbTex.Size			= texSize;

			mFbDepthTex.Handle	= fbtextures[0];
			mFbDepthTex.Size	= texSize;

			mFbHandle = bgfx::createFrameBuffer(BX_COUNTOF(fbtextures), fbtextures, true);
		}
	}
}
