/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Include/Transformation.hpp"

using namespace GameEngine;

quat Math::QuatFromAxisAngle(const vec3& axis, float angle)
{
	const vec3 naxis = axis.Normalized();
	const float half = angle * 0.5f;
	const float s = std::sin(half);
	return quat(
		std::cos(half),
		naxis.X * s,
		naxis.Y * s,
		naxis.Z * s
	);
}

quat Math::QuatFromEulerAngles(const EulerRotation& rot)
{
	float cy = std::cos(rot.Yaw * 0.5f);
	float sy = std::sin(rot.Yaw * 0.5f);
	float cp = std::cos(rot.Pitch * 0.5f);
	float sp = std::sin(rot.Pitch * 0.5f);
	float cr = std::cos(rot.Roll * 0.5f);
	float sr = std::sin(rot.Roll * 0.5f);

	return quat(
		cr * cp * cy + sr * sp * sy,
		sr * cp * cy - cr * sp * sy,
		cr * sp * cy + sr * cp * sy,
		cr * cp * sy - sr * sp * cy
	);
}
