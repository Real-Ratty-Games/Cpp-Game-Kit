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
	enum class DrawAPI
	{
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

	struct QuadVertex
	{
		float X;
		float Y;
		float U;
		float V;
	};

	struct InstanceData
	{
		bgfx::InstanceDataBuffer	Buffer;
		int							MissedAmount; // Amount of instances not rendered due to hardware limitations
	};
}
#endif