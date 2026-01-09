/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef MATRIX3_HPP_
#define MATRIX3_HPP_
#include "SystemTypes.hpp"
#include "Arithmetic.hpp"

namespace GameEngine
{
	/// <summary>
	/// Matrix 4x4
	/// </summary>
	/// <typeparam name="T"></typeparam>
	template<typename T>
	class Matrix4 : public IArithmetic
	{
	public:
		T Data[16];

		Matrix4<T>() : Data{} {}

		T& operator()(int row, int col) { return Data[row * 4 + col]; }
		const T& operator()(int row, int col) const { return Data[row * 4 + col]; }

		bool operator == (const Matrix4<T>& other) const
		{
			for (uint64 i = 0; i < 16; i++)
			{
				if (Data[i] != other.Data[i])
					return false;
			}
			return true;
		}

		Matrix4<T> operator +(const Matrix4<T>& other) const
		{
			Matrix4<T> result;
			for (uint64 i = 0; i < 16; i++)
				result[i] = Data[i] + other.Data[i];
			return result;
		}

		Matrix4<T> operator -(const Matrix4<T>& other) const
		{
			Matrix4<T> result;
			for (uint64 i = 0; i < 16; i++)
				result[i] = Data[i] - other.Data[i];
			return result;
		}

		Matrix4<T> operator *(const Matrix4<T>& other) const
		{
			Matrix4<T> result;
			for (int row = 0; row < 4; row++)
				for (int col = 0; col < 4; col++)
					for (int k = 0; k < 4; k++)
						result(row, col) += Data(row, k) * other(k, col);
			return result;
		}

		Matrix4<T>& operator +=(const Matrix4<T>& other)
		{
			for (uint64 i = 0; i < 16; i++)
				Data[i] += other.Data[i];
			return *this;
		}

		Matrix4<T>& operator -=(const Matrix4<T>& other)
		{
			for (uint64 i = 0; i < 16; i++)
				Data[i] -= other.Data[i];
			return *this;
		}

		Matrix4<T>& operator *=(const Matrix4<T>& other)
		{
			Matrix4<T> result;
			for (int row = 0; row < 4; row++)
				for (int col = 0; col < 4; col++)
					for (int k = 0; k < 4; k++)
						result(row, col) += Data(row, k) * other(k, col);
			return result;
		}
	};
}
#endif