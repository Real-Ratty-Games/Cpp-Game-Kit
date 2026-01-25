/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Public/ScriptCore.hpp"
#include <lua/lauxlib.h>
#include <lua/lualib.h>

using namespace GameEngine;

void ScriptCore::Initialize()
{
	mState = luaL_newstate();
	luaL_openlibs(mState);
}

void ScriptCore::Release()
{
	if (mState != nullptr)
	{
		lua_close(mState);
		mState = nullptr;
	}
}

lua_State* ScriptCore::State()
{
	return mState;
}
