/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef SYSTEMTYPES_HPP_
#define SYSTEMTYPES_HPP_
#include <string>

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
}
#endif