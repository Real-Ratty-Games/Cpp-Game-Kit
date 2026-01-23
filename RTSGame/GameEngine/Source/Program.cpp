/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Public/Program.hpp"

using namespace GameEngine;

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
