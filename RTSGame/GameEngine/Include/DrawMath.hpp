/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef DRAWMATH_HPP_
#define DRAWMATH_HPP_
#include "SystemTypes.hpp"
#include "DrawData.hpp"
#include "Viewport3D.hpp"

namespace GameEngine::Math
{
	vec3 ScreenLocation2WorldLocation(const vec2& screenLocation, const vec2& screenSize,
		const Viewport3D& viewport3D, const float& distance);
}
#endif