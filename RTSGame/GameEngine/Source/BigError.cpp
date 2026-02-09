/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Include/BigError.hpp"
#include "../Include/Window.hpp"

using namespace GameEngine;

BigError::BigError(const strg& message) : std::runtime_error(message)
{
#if !_DEBUG
	if (Window::IsSDLInit())
	{
		if (Window::IsSplashScreenVisible())
			Window::DestroySplashScreen();
		SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_ERROR, "Fatal Error", message.data(), nullptr);
	}
#endif
}
