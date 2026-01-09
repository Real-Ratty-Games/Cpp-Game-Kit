/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef VECTOR3_HPP_
#define VECTOR3_HPP_

namespace GameEngine
{
	/// <summary>
	/// Vector 3D
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class Vector3
	{
	public:
		T X;
		T Y;
		T Z;

        Vector3() : X(T{}), Y(T{}), Z(T{}) {}

		Vector3(T vl)
		{
			X = Y = Z = vl;
		}

		Vector3(T x, T y, T z)
		{
			X = x;
			Y = y;
			Z = z;
		}

		Vector3(const Vector3& vec)
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
        static Vector3<T> Cross(const Vector3<T>& left, const Vector3<T>& right)
        {
            return Vector3<T>(
                left.Y * right.Z - left.Z * right.Y,
                left.Z * right.X - left.X * right.Z,
                left.X * right.Y - left.Y * right.X
            );
        }

        bool operator == (const Vector3<T>& other) const
        {
            return (X == other.X && Y == other.Y && Z == other.Z);
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