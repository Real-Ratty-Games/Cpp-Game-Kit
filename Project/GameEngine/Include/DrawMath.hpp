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
	GAMEENGINEAPI vec3 ScreenLocation2WorldLocation(const vec2& screenLocation, const vec2& screenSize,
		const Viewport3D& viewport3D, const float& distance);

	GAMEENGINEAPI vec3 ScreenLocation2WorldLocationPY(const vec2& screenLocation, const vec2& screenSize,
		const Viewport3D& viewport3D, const float& yplane);

	GAMEENGINEAPI vec3 ScreenLocation2WorldLocationPX(const vec2& screenLocation, const vec2& screenSize,
		const Viewport3D& viewport3D, const float& xplane);

	GAMEENGINEAPI vec3 ScreenLocation2WorldLocationPZ(const vec2& screenLocation, const vec2& screenSize,
		const Viewport3D& viewport3D, const float& zplane);

	GAMEENGINEAPI vec3 ScreenLocation2WorldLocation(const vec2& screenLocation, const vec2& screenSize,
		const ViewportOrtho3D& viewport3D);

	GAMEENGINEAPI vec3 ScreenLocation2WorldLocationPY(const vec2& screenLocation, const vec2& screenSize,
		const ViewportOrtho3D& viewport3D, const float& yplane);

	GAMEENGINEAPI vec3 ScreenLocation2WorldLocationPX(const vec2& screenLocation, const vec2& screenSize,
		const ViewportOrtho3D& viewport3D, const float& xplane);

	GAMEENGINEAPI vec3 ScreenLocation2WorldLocationPZ(const vec2& screenLocation, const vec2& screenSize,
		const ViewportOrtho3D& viewport3D, const float& zplane);
}
#endif