/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef SCRIPTCORE_HPP_
#define SCRIPTCORE_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include <lua/lua.hpp>

namespace GameEngine
{
	/// <summary>
	/// Manages lua core
	/// </summary>
	class GAMEENGINEAPI ScriptCore
	{
	public:
		void		Initialize();
		void		Release();
		lua_State*	State();

	private:
		lua_State* mState = nullptr;
	};
}
#endif