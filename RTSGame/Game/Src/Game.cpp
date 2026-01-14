/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Inc/Game.hpp"
#include "../Inc/GameWindow.hpp"

#include <Renderer.hpp>

using namespace GameEngine::Draw;

using namespace MyGame;

bool GameProgram::Initialize()
{
	Window::Initialize();
	Window::ShowSplashScreen();

	mWindow = new GameWindow(this);
	mWindow->Show("My Game", 1280, 720, false);

	if (!Renderer::Initialize(mWindow, DrawAPI::DIRECT3D12))
		return false;
	
	Window::DestroySplashScreen();
	return true;
}

void GameProgram::Tick()
{
	mWindow->PollEvent();
}

void GameProgram::Draw()
{
	Renderer::BeginDraw(mWindow, true, MSAA::X16);
	if (!mWindow->IsIconified())
	{

		Renderer::Printf(vec2i(0, 0), 0x0f, "Hello, World!");

	}
	Renderer::EndDraw();
}

void GameProgram::Cleanup()
{
	Renderer::Release();

	if (mWindow != nullptr)
	{
		mWindow->Release();
		delete mWindow;
		mWindow = nullptr;
	}
	Window::Release();
}
