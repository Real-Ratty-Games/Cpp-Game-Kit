/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Inc/ScriptException.hpp"

using namespace GameEngine::Script;

ScriptException::ScriptException(strgv msg)
{
	mMsg = msg;
}

void ScriptException::Throw(strgv msg)
{
	throw ScriptException(msg);
}

cstrg ScriptException::what() const noexcept
{
	return mMsg.c_str();
}

