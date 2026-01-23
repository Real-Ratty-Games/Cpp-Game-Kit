/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Inc/GameWindow.hpp"
#include "../Inc/Game.hpp"
#include <Renderer.hpp>

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
	case SDL_EVENT_WINDOW_RESIZED:
	{
		vec2i size = GetSize();
		Renderer::OnResize(size, true, MSAA::X16);
		dynamic_cast<GameProgram*>(pProgram)->OnResize(size);
	}break;
	}
}
