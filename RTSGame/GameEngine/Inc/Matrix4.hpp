/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef MATRIX4_HPP_
#define MATRIX4_HPP_

namespace GameEngine::Math
{
	/// <summary>
	/// Matrix 4x4
	/// row-major style
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class Matrix4
	{
	public:
		T Data[16];

		static Matrix4<T> Identity()
		{
			return Matrix4<T>(1, 0, 0, 0,
				0, 1, 0, 0,
				0, 0, 1, 0,
				0, 0, 0, 1);
		}

		Matrix4<T>() : Data{} {}

		Matrix4<T>(T vl)
			: Data {
				vl, vl, vl, vl,
				vl, vl, vl, vl,
				vl, vl, vl, vl,
				vl, vl, vl, vl
		} { }

		Matrix4<T>(T a1, T a2, T a3, T a4,
			T b1, T b2, T b3, T b4, 
			T c1, T c2, T c3, T c4, 
			T d1, T d2, T d3, T d4)
			: Data{
			a1, a2, a3, a4,
			b1, b2, b3, b4,
			c1, c2, c3, c4,
			d1, d2, d3, d4
		} { }

		inline T* Ptr()
		{
			return &Data[0];
		}

		inline const T* Ptr() const
		{
			return &Data[0];
		}

		T& operator()(int row, int col) { return Data[row * 4 + col]; }
		const T& operator()(int row, int col) const { return Data[row * 4 + col]; }

		bool operator == (const Matrix4<T>& other) const
		{
			for (size_t i = 0; i < 16; i++)
			{
				if (Data[i] != other.Data[i])
					return false;
			}
			return true;
		}

		Matrix4<T> operator +(const Matrix4<T>& other) const
		{
			Matrix4<T> result(T(0));
			for (size_t i = 0; i < 16; i++)
				result.Data[i] = Data[i] + other.Data[i];
			return result;
		}

		Matrix4<T> operator -(const Matrix4<T>& other) const
		{
			Matrix4<T> result(T(0));
			for (size_t i = 0; i < 16; i++)
				result.Data[i] = Data[i] - other.Data[i];
			return result;
		}

		Matrix4<T> operator *(const Matrix4<T>& other) const
		{
			Matrix4<T> result(T(0));
			for (int row = 0; row < 4; row++)
				for (int col = 0; col < 4; col++)
					for (int k = 0; k < 4; k++)
						result(row, col) += Data[row * 4 + k] * other(k, col);
			return result;
		}

		Matrix4<T>& operator +=(const Matrix4<T>& other)
		{
			for (size_t i = 0; i < 16; i++)
				Data[i] += other.Data[i];
			return *this;
		}

		Matrix4<T>& operator -=(const Matrix4<T>& other)
		{
			for (size_t i = 0; i < 16; i++)
				Data[i] -= other.Data[i];
			return *this;
		}

		Matrix4<T>& operator *=(const Matrix4<T>& other)
		{
			Matrix4<T> result(T(0));
			for (int row = 0; row < 4; row++)
				for (int col = 0; col < 4; col++)
					for (int k = 0; k < 4; k++)
						result(row, col) += Data[row * 4 + k] * other(k, col);
			*this = result;
			return *this;
		}
	};
}
#endif