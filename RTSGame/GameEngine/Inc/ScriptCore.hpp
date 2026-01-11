/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef SCRIPTCORE_HPP_
#define SCRIPTCORE_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include <lua.hpp>

using namespace GameEngine::Core;

namespace GameEngine::Script
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