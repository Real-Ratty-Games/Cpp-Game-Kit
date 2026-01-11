/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Inc/Program.hpp"

using namespace GameEngine::Core;

void Program::Run()
{
	if (Initialize())
	{
		while (!bQuit)
		{
			Tick();
			Draw();
		}
	}
	Cleanup();
}

void Program::Quit(bool vl)
{
	bQuit = vl;
}
