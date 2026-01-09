/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef SYSTEMTYPES_HPP_
#define SYSTEMTYPES_HPP_
#include <string>
#include "Vector2.hpp"
#include "Vector3.hpp"
#include "Vector4.hpp"
#include "Matrix4.hpp"

/// <summary>
/// Shorter, more clearer system types
/// </summary>
namespace GameEngine
{
	typedef const char*				cstrg;
	typedef std::string				strg;
	typedef std::string_view		strgv;
	typedef signed char				int8;
	typedef short					int16;
	typedef signed long long		int64;
	typedef unsigned int			uint;
	typedef unsigned char			uint8;
	typedef unsigned short			uint16;
	typedef unsigned long long		uint64;
	typedef unsigned long			ulong;
	typedef Vector2<int>			ivec2;
	typedef Vector2<float>			vec2;
	typedef Vector2<double>			dvec2;
	typedef Vector3<int>			ivec3;
	typedef Vector3<float>			vec3;
	typedef Vector3<double>			dvec3;
	typedef Vector4<int>			ivec4;
	typedef Vector4<float>			vec4;
	typedef Vector4<double>			dvec4;
	typedef Matrix4<int>			imat4;
	typedef Matrix4<float>			mat4;
	typedef Matrix4<double>			dmat4;
}
#endif