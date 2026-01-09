/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef VECTOR2_HPP_
#define VECTOR2_HPP_
#include "SystemTypes.hpp"
#include "Arithmetic.hpp"

namespace GameEngine
{
	template<typename T>
	class Vector2 : public IArithmetic
	{
	public:
		T X;
		T Y;

		Vector2<T>(T vl)
		{
			X = Y = vl;
		}

		Vector2<T>(T x, T y)
		{
			X = x;
			Y = y;
		}

		Vector2<T>(Vector2<T> vec)
		{
			X = vec.X;
			Y = vec.Y;
		}

		bool operator == (const Vector2<T>& other) const
		{
			return (X == other.X && Y == other.Y);
		}

		bool operator < (const Vector2<T>& other) const
		{
			return (X < other.X && Y < other.Y);
		}

		bool operator <= (const Vector2<T>& other) const
		{
			return (X <= other.X && Y <= other.Y);
		}

		bool operator > (const Vector2<T>& other) const
		{
			return (X > other.X && Y > other.Y);
		}

		bool operator >= (const Vector2<T>& other) const
		{
			return (X >= other.X && Y >= other.Y);
		}

		Vector2<T> operator +(const Vector2<T>& other) const
		{
			return Vector2<T>(X + other.X, Y + other.Y);
		}

		Vector2<T> operator -(const Vector2<T>& other) const
		{
			return Vector2<T>(X - other.X, Y - other.Y);
		}

		Vector2<T> operator *(const Vector2<T>& other) const
		{
			return Vector2<T>(X * other.X, Y * other.Y);
		}

		Vector2<T> operator /(const Vector2<T>& other) const
		{
			return Vector2<T>(X / other.X, Y / other.Y);
		}

		Vector2<T>& operator +=(const Vector2<T>& other)
		{
			X += other.X;
			Y += other.Y;
			return *this;
		}

		Vector2<T>& operator -=(const Vector2<T>& other)
		{
			X -= other.X;
			Y -= other.Y;
			return *this;
		}

		Vector2<T>& operator *=(const Vector2<T>& other)
		{
			X *= other.X;
			Y *= other.Y;
			return *this;
		}

		Vector2<T>& operator /=(const Vector2<T>& other)
		{
			X /= other.X;
			Y /= other.Y;
			return *this;
		}
	};
}
#endif