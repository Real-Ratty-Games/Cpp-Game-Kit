/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef MATH_HPP_
#define MATH_HPP_

#define GAMEENGINE_MATH_PI 3.14159

namespace GameEngine::Math
{
	template<typename T>
	constexpr T Min(T a, T b) noexcept
	{
		return a < b ? a : b;
	}

	template<typename T>
	constexpr T Max(T a, T b) noexcept
	{
		return a > b ? a : b;
	}

	template<typename T>
	constexpr T Abs(T v) noexcept
	{
		return v < T(0) ? -v : v;
	}

	template<typename T>
	constexpr T ToRadians(const T& vl) noexcept
	{
		return (T(GAMEENGINE_MATH_PI) / T(180)) * vl;
	}

	template<typename T>
	constexpr T ToDegree(const T& vl) noexcept
	{
		return (T(180) / T(GAMEENGINE_MATH_PI)) * vl;
	}

	template<typename T>
	inline T Distance(const Vector2<T>& a, const Vector2<T>& b)
	{
		return (a - b).Length();
	}

	template<typename T>
	inline T Distance(const Vector3<T>& a, const Vector3<T>& b)
	{
		return (a - b).Length();
	}

	template<typename T>
	inline T Distance(const Vector4<T>& a, const Vector4<T>& b)
	{
		return (a - b).Length();
	}
}
#endif
