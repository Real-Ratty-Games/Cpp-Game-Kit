/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Inc/Game.hpp"
#include "../Inc/GameWindow.hpp"

using namespace MyGame;

bool GameProgram::Initialize()
{
	Window::Initialize();
	Window::ShowSplashScreen();

	mWindow = new GameWindow(this);
	mWindow->Show("My Game", 1280, 720, false);
	
	Window::DestroySplashScreen();
	return true;
}

void GameProgram::Tick()
{
	mWindow->PollEvent();
}

void GameProgram::Draw()
{

}

void GameProgram::Cleanup()
{
	if (mWindow != nullptr)
	{
		mWindow->Release();
		delete mWindow;
		mWindow = nullptr;
	}
	Window::Release();
}
