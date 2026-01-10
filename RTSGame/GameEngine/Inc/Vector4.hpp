/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef VECTOR4_HPP_
#define VECTOR4_HPP_

namespace GameEngine::Math
{
	/// <summary>
	/// Vector 4D
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class Vector4
	{
	public:
		T X;
		T Y;
		T Z;
		T W;

        Vector4() : X(T{}), Y(T{}), Z(T{}), W(T{}) {}

		Vector4(T vl)
		{
			X = Y = Z = W = vl;
		}

		Vector4(T x, T y, T z, T w)
		{
			X = x;
			Y = y;
			Z = z;
			W = w;
		}

		Vector4(const Vector4& vec)
		{
			X = vec.X;
			Y = vec.Y;
			Z = vec.Z;
			W = vec.W;
		}

        bool operator == (const Vector4<T>& other) const
        {
            return (X == other.X && Y == other.Y && Z == other.Z && W == other.W);
        }

        Vector4<T> operator +(const Vector4<T>& other) const
        {
            return Vector4<T>(X + other.X, Y + other.Y, Z + other.Z, W + other.W);
        }

        Vector4<T> operator -(const Vector4<T>& other) const
        {
            return Vector4<T>(X - other.X, Y - other.Y, Z - other.Z, W - other.W);
        }

        Vector4<T> operator *(const Vector4<T>& other) const
        {
            return Vector4<T>(X * other.X, Y * other.Y, Z * other.Z, W * other.W);
        }

        Vector4<T> operator /(const Vector4<T>& other) const
        {
            return Vector4<T>(X / other.X, Y / other.Y, Z / other.Z, W / other.W);
        }

        Vector4<T>& operator +=(const Vector4<T>& other)
        {
            X += other.X;
            Y += other.Y;
            Z += other.Z;
            W += other.W;
            return *this;
        }

        Vector4<T>& operator -=(const Vector4<T>& other)
        {
            X -= other.X;
            Y -= other.Y;
            Z -= other.Z;
            W -= other.W;
            return *this;
        }

        Vector4<T>& operator *=(const Vector4<T>& other)
        {
            X *= other.X;
            Y *= other.Y;
            Z *= other.Z;
            W *= other.W;
            return *this;
        }

        Vector4<T>& operator /=(const Vector4<T>& other)
        {
            X /= other.X;
            Y /= other.Y;
            Z /= other.Z;
            W /= other.W;
            return *this;
        }
    };
}
#endif