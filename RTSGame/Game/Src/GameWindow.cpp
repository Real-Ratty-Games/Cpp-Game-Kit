/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Inc/GameWindow.hpp"

using namespace MyGame;

GameWindow::GameWindow(Program* program)
{
	pProgram = program;
}

void GameWindow::EventCallback()
{
	switch (mWndEvent.type)
	{
	case SDL_EVENT_QUIT: pProgram->Quit(); break;
	case SDL_EVENT_WINDOW_MINIMIZED: bIconified = true; break;
	case SDL_EVENT_WINDOW_RESTORED: bIconified = false; break;
	case SDL_EVENT_WINDOW_RESIZED: bResized = true; break;
	}
}
