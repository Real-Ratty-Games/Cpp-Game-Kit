/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Include/DrawMath.hpp"
#include "../Include/Renderer.hpp"
#include "../Include/Transformation.hpp"
#include "../Include/Multiply.hpp"
#include <bx/math.h>

using namespace GameEngine;

vec3 Math::ScreenLocation2WorldLocation(const vec2& screenLocation, const vec2& screenSize,
	const Viewport3D& viewport3D, const float& distance)
{
	const float glCoordX = (2.0f * screenLocation.X) / screenSize.X - 1.0f;
	const float glCoordY = -((2.0f * screenLocation.Y) / screenSize.Y - 1.0f);
	vec4 clipCoords = vec4(glCoordX, glCoordY, -1.0f, 1.0f);

	float proj[16];
	bx::mtxProj(proj, viewport3D.Fov, screenSize.X / screenSize.Y, 0.01f, 10000.0f, bgfx::getCaps()->homogeneousDepth);

	mat4 projMat(proj);
	mat4 invertedProjection;
	if (!projMat.Inverse(invertedProjection))
		invertedProjection = projMat;

	vec4 eyeCoord = Multiply(invertedProjection, clipCoords);

	mat4 view = viewport3D.View();
	mat4 invertedView;
	if (!view.Inverse(invertedView))
		invertedView = view;

	vec4 rayWorld = Multiply(invertedView, eyeCoord);
	vec3 screenRay = vec3(rayWorld.X, rayWorld.Y, rayWorld.Z);
	screenRay = screenRay.Normalized();

	return viewport3D.Eye + screenRay * distance;
}
