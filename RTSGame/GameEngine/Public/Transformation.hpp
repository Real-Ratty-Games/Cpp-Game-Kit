/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef TRANSFORMATION_HPP_
#define TRANSFORMATION_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"

#define GAMEENGINE_MATH_PI 3.14159

namespace GameEngine::Math
{
	GAMEENGINEAPI mat4 Translate(const mat4& mat, const vec3& v);
	GAMEENGINEAPI mat4 Scale(const mat4& mat, const vec3& v);
	GAMEENGINEAPI mat4 Rotate(const mat4& mat, const vec3& axis, float angle);
	
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