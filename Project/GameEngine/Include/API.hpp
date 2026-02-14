/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef API_HPP_
#define API_HPP_

#if WIN32
    #ifdef GAMEENGINEAPI_EXPORT
        #define GAMEENGINEAPI __declspec(dllexport)
    #else
        #define GAMEENGINEAPI __declspec(dllimport)
    #endif
#elif __APPLE__
    #ifdef GAMEENGINEAPI_EXPORT
        #define GAMEENGINEAPI __attribute__((visibility("default")))
    #else
        #define GAMEENGINEAPI
    #endif
#else
    #ifdef GAMEENGINEAPI_EXPORT
        #define GAMEENGINEAPI __attribute__((visibility("default")))
    #else
        #define GAMEENGINEAPI
    #endif
#endif

#endif
