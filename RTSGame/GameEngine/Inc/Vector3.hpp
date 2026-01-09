/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_
#include "SystemTypes.hpp"
#include "Arithmetic.hpp"

namespace GameEngine
{
	/// <summary>
	/// Vector 3D
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class Vector3 : public IArithmetic
	{
	public:
		T X;
		T Y;
		T Z;

        Vector3<T>()
        { }

		Vector3<T>(T vl)
		{
			X = Y = Z = vl;
		}

		Vector3<T>(T x, T y, T z)
		{
			X = x;
			Y = y;
			Z = z;
		}

		Vector3<T>(Vector3<T> vec)
		{
			X = vec.X;
			Y = vec.Y;
			Z = vec.Z;
		}

        /// <summary>
        /// Right hand cross product
        /// </summary>
        /// <param name="left"></param>
        /// <param name="right"></param>
        /// <returns></returns>
        static Vector3<T> Cross(Vector3<T> left, Vector3<T> right)
        {
            return new Vector3<T>
            {
                X = left.Y * right.Z - left.Z * right.Y,
                Y = left.Z * right.X - left.X * right.Z,
                Z = left.X * right.Y - left.Y * right.X
            };
        }

        bool operator == (const Vector3<T>& other) const
        {
            return (X == other.X && Y == other.Y && Z == other.Z);
        }

        bool operator < (const Vector3<T>& other) const
        {
            return (X < other.X && Y < other.Y && Z < other.Z);
        }

        bool operator <= (const Vector3<T>& other) const
        {
            return (X <= other.X && Y <= other.Y && Z <= other.Z);
        }

        bool operator > (const Vector3<T>& other) const
        {
            return (X > other.X && Y > other.Y && Z > other.Z);
        }

        bool operator >= (const Vector3<T>& other) const
        {
            return (X >= other.X && Y >= other.Y && Z >= other.Z);
        }

        Vector3<T> operator +(const Vector3<T>& other) const
        {
            return Vector3<T>(X + other.X, Y + other.Y, Z + other.Z);
        }

        Vector3<T> operator -(const Vector3<T>& other) const
        {
            return Vector3<T>(X - other.X, Y - other.Y, Z - other.Z);
        }

        Vector3<T> operator *(const Vector3<T>& other) const
        {
            return Vector3<T>(X * other.X, Y * other.Y, Z * other.Z);
        }

        Vector3<T> operator /(const Vector3<T>& other) const
        {
            return Vector3<T>(X / other.X, Y / other.Y, Z / other.Z);
        }

        Vector3<T>& operator +=(const Vector3<T>& other)
        {
            X += other.X;
            Y += other.Y;
            Z += other.Z;
            return *this;
        }

        Vector3<T>& operator -=(const Vector3<T>& other)
        {
            X -= other.X;
            Y -= other.Y;
            Z -= other.Z;
            return *this;
        }

        Vector3<T>& operator *=(const Vector3<T>& other)
        {
            X *= other.X;
            Y *= other.Y;
            Z *= other.Z;
            return *this;
        }

        Vector3<T>& operator /=(const Vector3<T>& other)
        {
            X /= other.X;
            Y /= other.Y;
            Z /= other.Z;
            return *this;
        }
	};
}
#endif