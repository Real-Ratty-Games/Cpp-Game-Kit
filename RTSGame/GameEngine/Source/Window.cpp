/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Public/Window.hpp"
#include <stdexcept>

using namespace GameEngine;

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
		throw new std::runtime_error(errmsg);
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
/// Create window
/// </summary>
/// <param name="title"></param>
/// <param name="width"></param>
/// <param name="height"></param>
/// <param name="fs">fullscreen</param>
void Window::Create(strgv title, uint width, uint height, bool fs)
{
	bFullscreen = fs;
	if ((mWndHandle = SDL_CreateWindow(title.data(), (int)width, (int)height, (fs ? SDL_WINDOW_FULLSCREEN : 0) | SDL_WINDOW_HIDDEN)) == nullptr)
	{
		const strg errmsg = "Failed creating window: " + strg(SDL_GetError());
		throw new std::runtime_error(errmsg);
	}
}

/// <summary>
/// Show/Hide window
/// </summary>
/// <param name="vl">True if show</param>
void Window::Show(bool vl)
{
	if (vl) SDL_ShowWindow(mWndHandle);
	else SDL_HideWindow(mWndHandle);
}

/// <summary>
/// Poll window events
/// </summary>
void Window::PollEvent()
{
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
	bFullscreen = vl;
	SDL_SetWindowFullscreen(mWndHandle, vl);
}

/// <summary>
/// Switch fullscreen mode
/// </summary>
void Window::SwitchFullscreen()
{
	SetFullscreen(!bFullscreen);
}
 
/// <summary>
/// Returns window size
/// </summary>
/// <returns></returns>
vec2i Window::GetSize()
{
	int w, h;
	SDL_GetWindowSize(mWndHandle, &w, &h);
	return vec2i(w, h);
}

/// <summary>
/// Returns true if fullscreen mode is on
/// </summary>
/// <returns></returns>
bool Window::GetFullscreen()
{
	return bFullscreen;
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
