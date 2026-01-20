/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Inc/Game.hpp"
#include <DebugHelp.hpp>

using namespace MyGame;

int main()
{
#if _DEBUG
	DEBUGHELP_LOOK4MEMLEAKS();
#endif
	DEBUGHELP_SHOWCMD(false);

	GameProgram program;
	program.Run();
	return 0;
}
