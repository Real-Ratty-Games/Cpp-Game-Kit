/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef DRAWSURFACE_HPP_
#define DRAWSURFACE_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include "DrawData.hpp"

using namespace GameEngine::Core;

namespace GameEngine::Draw
{
	class GAMEENGINEAPI DrawSurface
	{
	public:
		DrawSurface(uint16 viewid, void* wndHandle);
		void Release();
		void Clear();
		void OnResize(vec2 size);
		uint16 ViewID() const;

	private:
		void DestroyFB();
		void SetFBViewId();
		void UpdateFB(vec2i texSize, bgfx::TextureFormat::Enum format = bgfx::TextureFormat::RGBA8);

	public:
		vec2i					Location;
		vec2					Resolution;
		vec2					AspectRatio;
		uint					ClearColor;
		bool					bTopMost;
		bool					bTransparent;

	private:
		bgfx::FrameBufferHandle mFbHandle;
		Texture					mFbTex;

		uint16					mViewId;
		void*					pWindowHandle;
	};
}
#endif