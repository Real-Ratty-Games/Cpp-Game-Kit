/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef TRANSFORMATION_HPP_
#define TRANSFORMATION_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include "EulerRotation.hpp"

#define GAMEENGINE_MATH_PI 3.14159

namespace GameEngine::Math
{
	GAMEENGINEAPI mat4 Translate(const mat4& mat, const vec3& v);
	GAMEENGINEAPI mat4 Scale(const mat4& mat, const vec3& v);

	/// angle in radians
	GAMEENGINEAPI mat4 Rotate(const mat4& mat, const vec3& axis, float angle);
	GAMEENGINEAPI vec3 Rotate(const quat& q, const vec3& v);

	/// angle in radians
	GAMEENGINEAPI quat QuatFromAxisAngle(const vec3& axis, float angle);
	GAMEENGINEAPI quat QuatFromEulerAngles(const EulerRotation& rot);
	
	template<typename T>
	inline T ToRadians(const T& vl)
	{
		return (T(GAMEENGINE_MATH_PI) / T(180)) * vl;
	}

	template<typename T>
	inline T ToDegree(const T& vl)
	{
		return (T(180) / T(GAMEENGINE_MATH_PI)) * vl;
	}
}
#endif