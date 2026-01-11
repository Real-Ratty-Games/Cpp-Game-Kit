/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Inc/ScriptCore.hpp"
#include <lauxlib.h>
#include <lualib.h>

using namespace GameEngine::Script;

/// <summary>
/// Create lua core
/// </summary>
void ScriptCore::Initialize()
{
	mState = luaL_newstate();
	luaL_openlibs(mState);
}

/// <summary>
/// Free lua core
/// </summary>
void ScriptCore::Release()
{
	if (mState != nullptr)
	{
		lua_close(mState);
		mState = nullptr;
	}
}

/// <summary>
/// Returns lua state
/// </summary>
/// <returns></returns>
lua_State* ScriptCore::State()
{
	return mState;
}
