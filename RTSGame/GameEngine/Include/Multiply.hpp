/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef MULTIPLY_HPP_
#define MULTIPLY_HPP_
#include "SystemTypes.hpp"
#include "Vector4.hpp"
#include "Matrix4.hpp"

namespace GameEngine::Math
{
	template<typename T>
	Vector4<T> Multiply(const Matrix4<T>& left, const Vector4<T>& right)
	{
		return Vector4<T>(
			left(0, 0) * right.X + left(0, 1) * right.Y + left(0, 2) * right.Z + left(0, 3) * right.W,
			left(1, 0) * right.X + left(1, 1) * right.Y + left(1, 2) * right.Z + left(1, 3) * right.W,
			left(2, 0) * right.X + left(2, 1) * right.Y + left(2, 2) * right.Z + left(2, 3) * right.W,
			left(3, 0) * right.X + left(3, 1) * right.Y + left(3, 2) * right.Z + left(3, 3) * right.W
		);
	}
}
#endif