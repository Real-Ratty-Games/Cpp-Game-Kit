/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef DRAWDATA_HPP_
#define DRAWDATA_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#if _DEBUG
#define BX_CONFIG_DEBUG 1
#else
#define BX_CONFIG_DEBUG 0
#endif
#include <bgfx/bgfx.h>
#include <bgfx/platform.h>

using namespace GameEngine::Core;

namespace GameEngine::Draw
{
	class Sprite;

	enum class DrawAPI
	{
		DIRECT3D11	= bgfx::RendererType::Direct3D11,
		DIRECT3D12	= bgfx::RendererType::Direct3D12,
		VULKAN		= bgfx::RendererType::Vulkan
	};

	enum class MSAA : uint
	{
		NONE	= 0,
		X2		= 0x00000010,
		X4		= 0x00000020,
		X8		= 0x00000030,
		X16		= 0x00000040
	};

	struct Color
	{
		float R;
		float G;
		float B;
		float A;

		Color()
		{
			R = G = B = A = 1.0f;
		}

		Color(float vl)
		{
			R = G = B = A = vl;
		}

		Color(float r, float g, float b, float a)
		{
			R = r;
			G = g;
			B = b;
			A = a;
		}
	};

	struct QuadVertex
	{
		float X;
		float Y;
		float U;
		float V;
	};

	struct InstanceData
	{
		Sprite*						pSprite;
		bgfx::InstanceDataBuffer	Buffer;
		int							MissedAmount; // Amount of instances not rendered due to hardware limitations
	};

	struct Texture
	{
		bgfx::TextureHandle Handle = BGFX_INVALID_HANDLE;
		vec2i				Size;
	};

	struct Camera2D
	{
		vec2 Location;
		vec2 Size;
	};

	struct Transform2D
	{
		vec2	Location;
		vec2	Scale;
		float	Rotation;
		Color	ImageColor;

		Transform2D()
		{
			Location	= vec2(0.0f);
			Scale		= vec2(1.0f);
			Rotation	= 0.0f;
		}
	};

	struct TransformAtlas2D : public Transform2D
	{
		vec2	Index;

		TransformAtlas2D() : Transform2D()
		{
			Index		= vec2(0.0f);
		}
	};
}
#endif