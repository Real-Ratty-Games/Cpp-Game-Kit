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

vec3 Math::Rotate(const quat& q, const vec3& v)
{
	quat p(0, v.X, v.Y, v.Z);
	quat qInv = q.Conjugate();
	quat result = q * p * qInv;
	return { result.X, result.Y, result.Z };
}

quat Math::QuatFromAxisAngle(const vec3& axis, float angle)
{
	float half = angle * 0.5f;
	float s = std::sin(half);
	return quat(
		std::cos(half),
		axis.X * s,
		axis.Y * s,
		axis.Z * s
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
