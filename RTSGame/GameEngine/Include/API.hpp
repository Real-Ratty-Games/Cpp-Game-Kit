/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef API_HPP_
#define API_HPP_

#ifdef GAMEENGINEAPI_EXPORT
	#define GAMEENGINEAPI __declspec(dllexport)
#else
	#define GAMEENGINEAPI __declspec(dllimport)
#endif

#endif