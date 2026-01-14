/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Inc/DrawException.hpp"

using namespace GameEngine::Draw;

DrawException::DrawException(strgv msg)
{
	mMsg = msg;
}

void DrawException::Throw(strgv msg)
{
	throw DrawException(msg);
}

cstrg DrawException::what() const noexcept
{
	return mMsg.c_str();
}
