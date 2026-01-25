/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Public/Transformation.hpp"

using namespace GameEngine;

mat4 Math::Translate(const mat4& mat, const vec3& v)
{
	mat4 result = mat4::Identity();
	result(3, 0) = v.X;
	result(3, 1) = v.Y;
	result(3, 2) = v.Z;
	return result * mat;
}

mat4 Math::Scale(const mat4& mat, const vec3& v)
{
	mat4 result = mat4::Identity();
	result(0, 0) = v.X;
	result(1, 1) = v.Y;
	result(2, 2) = v.Z;
	return result * mat;
}

mat4 Math::Rotate(const mat4& mat, const vec3& axis, float angle)
{
	const vec3	u = axis.Normalized();
	const float c = cos(angle);
	const float s = sin(angle);
	const float t = 1 - c;

	mat4 result = mat4::Identity();
	result(0,0) = t * u.X * u.X + c;
	result(1,0) = t * u.X * u.Y - s * u.Z;
	result(2,0) = t * u.X * u.Z + s * u.Y;

	result(0,1) = t * u.X * u.Y + s * u.Z;
	result(1,1) = t * u.Y * u.Y + c;
	result(2,1) = t * u.Y * u.Z - s * u.X;

	result(0,2) = t * u.X * u.Z - s * u.Y;
	result(1,2) = t * u.Y * u.Z + s * u.X;
	result(2,2) = t * u.Z * u.Z + c;
	return result * mat;
}
