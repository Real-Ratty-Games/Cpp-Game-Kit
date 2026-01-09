/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef ARITHMETIC_HPP_
#define ARITHMETIC_HPP_
#include "SystemTypes.hpp"

namespace GameEngine
{
	/// <summary>
	/// Class interface for arithmetic objects
	/// </summary>
	class IArithmetic
	{
	public:
		virtual bool operator == (const IArithmetic& other) const = 0;
		virtual bool operator < (const IArithmetic& other) const = 0;
		virtual bool operator <= (const IArithmetic& other) const = 0;
		virtual bool operator > (const IArithmetic& other) const = 0;
		virtual bool operator >= (const IArithmetic& other) const = 0;
		virtual IArithmetic operator +(const IArithmetic& other) const = 0;
		virtual IArithmetic operator -(const IArithmetic& other) const = 0;
		virtual IArithmetic operator *(const IArithmetic& other) const = 0;
		virtual IArithmetic operator /(const IArithmetic& other) const = 0;
		virtual IArithmetic& operator +=(const IArithmetic& other) = 0;
		virtual IArithmetic& operator -=(const IArithmetic& other) = 0;
		virtual IArithmetic& operator *=(const IArithmetic& other) = 0;
		virtual IArithmetic& operator /=(const IArithmetic& other) = 0;
	};
}
#endif