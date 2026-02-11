/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef DRAWSURFACE3D_HPP_
#define DRAWSURFACE3D_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include "DrawData.hpp"
#include "DrawSurface.hpp"

namespace GameEngine
{
	class GAMEENGINEAPI DrawSurface3D : public DrawSurface
	{
	public:
		DrawSurface3D(uint16 viewid, vec2 size, void* wndHandle, bool depthOnly);
		Texture& GetDepthTexture();

	protected:
		void UpdateFB(vec2i texSize, bgfx::TextureFormat::Enum format = bgfx::TextureFormat::RGBA8) override;

	private:
		Texture	mFbDepthTex;
		bool	bDepthOnly;
	};
}
#endif