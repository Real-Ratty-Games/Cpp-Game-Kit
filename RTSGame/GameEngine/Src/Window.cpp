/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Inc/Window.hpp"

using namespace GameEngine::OS;

SDL_Window* Window::sSplashWndHandle = nullptr;
SDL_Renderer* Window::sSplashWndRenderer = nullptr;

/// <summary>
/// Initialize SDL3
/// </summary>
void Window::Initialize()
{
	if (!SDL_Init(SDL_INIT_VIDEO | SDL_INIT_GAMEPAD))
	{
		const strg errmsg = "Failed initializing SDL3: " + strg(SDL_GetError());
		throw new WindowException(errmsg);
	}
}

/// <summary>
/// Free SDL3
/// </summary>
void Window::Release()
{
	SDL_Quit();
}

/// <summary>
/// Show a splash screen with image
/// </summary>
void Window::ShowSplashScreen()
{
	SDL_Surface* surface = SDL_LoadBMP("Data/Splash.bmp");

	sSplashWndHandle = SDL_CreateWindow("Splash", surface->w, surface->h, SDL_WINDOW_BORDERLESS | SDL_WINDOW_ALWAYS_ON_TOP);
	sSplashWndRenderer = SDL_CreateRenderer(sSplashWndHandle, NULL);
	SDL_SetRenderDrawColor(sSplashWndRenderer, 0, 0, 0, 255);
	SDL_RenderClear(sSplashWndRenderer);

	if (surface != nullptr)
	{
		SDL_BlitSurface(surface, NULL, SDL_GetWindowSurface(sSplashWndHandle), NULL);

		SDL_Texture* splashTexture = SDL_CreateTextureFromSurface(sSplashWndRenderer, surface);
		SDL_DestroySurface(surface);

		SDL_RenderTexture(sSplashWndRenderer, splashTexture, NULL, NULL);
	}
	SDL_RenderPresent(sSplashWndRenderer);
}

/// <summary>
/// Set hardware cursor image
/// </summary>
/// <param name="img">format must be bmp</param>
void Window::SetHardwareCursorImage(strgv img)
{
	SDL_Surface* cursorSurface = SDL_LoadBMP(img.data());
	if (cursorSurface != nullptr)
	{
		SDL_Cursor* cursor = SDL_CreateColorCursor(cursorSurface, 0, 0);
		if (cursor != nullptr) SDL_SetCursor(cursor);
	}
}

/// <summary>
/// Destroy splash window
/// </summary>
void Window::DestroySplashScreen()
{
	SDL_DestroyRenderer(sSplashWndRenderer);
	SDL_DestroyWindow(sSplashWndHandle);
}

/// <summary>
/// Create and show window
/// </summary>
/// <param name="title"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="fs">fullscreen</param>
void Window::Show(strgv title, uint width, uint height, bool fs)
{
	if ((mWndHandle = SDL_CreateWindow(title.data(), (int)width, (int)height, fs ? SDL_WINDOW_FULLSCREEN : 0)) == nullptr)
	{
		const strg errmsg = "Failed creating window: " + strg(SDL_GetError());
		throw new WindowException(errmsg);
	}
}

/// <summary>
/// Poll window events
/// </summary>
void Window::PollEvent()
{
	bResized = false;
	while (SDL_PollEvent(&mWndEvent)) EventCallback();
}

/// <summary>
/// Close and cleanup window
/// </summary>
void Window::Destroy()
{
	SDL_DestroyWindow(mWndHandle);
}

/// <summary>
/// Returns true if window is minimized
/// </summary>
/// <returns></returns>
bool Window::IsIconified()
{
	return bIconified;
}

/// <summary>
/// Returns true if window was resized
/// </summary>
/// <returns></returns>
bool Window::IsResized()
{
	return bResized;
}

/// <summary>
/// Set window size in pixel
/// </summary>
/// <param name="width"></param>
/// <param name="height"></param>
void Window::SetSize(uint width, uint height)
{
	SDL_SetWindowSize(mWndHandle, (int)width, (int)height);
}

/// <summary>
/// Center window to monitor
/// </summary>
void Window::Center()
{
	SDL_SetWindowPosition(mWndHandle, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
}

/// <summary>
/// Switch fullscreen mode on or off
/// </summary>
/// <param name="vl"></param>
void Window::SetFullscreen(bool vl)
{
	SDL_SetWindowFullscreen(mWndHandle, vl);
}

vec2i Window::GetSize()
{
	int w, h;
	SDL_GetWindowSize(mWndHandle, &w, &h);
	return vec2i(w, h);
}

/// <summary>
/// Returns native OS window handle
/// </summary>
/// <returns></returns>
void* Window::GetNativePtr()
{
	SDL_PropertiesID wid = SDL_GetWindowProperties(mWndHandle);
#if _WIN32
	void* hwnd = SDL_GetPointerProperty(wid, SDL_PROP_WINDOW_WIN32_HWND_POINTER, nullptr);
#elif APPLE
	void* hwnd = SDL_GetPointerProperty(wid, SDL_PROP_WINDOW_COCOA_WINDOW_POINTER, nullptr);
#else
	void* hwnd = SDL_GetPointerProperty(wid, SDL_PROP_WINDOW_X11_WINDOW_NUMBER, nullptr);
#endif
	return hwnd;
}

/*======================================================
	WindowException
======================================================*/

WindowException::WindowException(strgv msg)
{
	mMsg = msg;
}

void WindowException::Throw(strgv msg)
{
	throw WindowException(msg);
}

cstrg WindowException::what() const noexcept
{
	return mMsg.c_str();
}
