/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef WINDOW_HPP_
#define WINDOW_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include <SDL3/SDL.h>

using namespace GameEngine::Core;

namespace GameEngine::OS
{
	/// <summary>
	/// Managing window creation and cleanup
	/// </summary>
	class GAMEENGINEAPI Window
	{
	public:
		inline static void Initialize();
		inline static void Release();
		static void ShowSplashScreen();
		static void DestroySplashScreen();
		static void SetHardwareCursorImage(strgv img);

		void Create(strgv title, uint width, uint height, bool fs);
		void Show(bool vl = true);
		void PollEvent();
		void Destroy();

		bool IsIconified();

		void SetSize(uint width, uint height);
		void Center();
		void SetFullscreen(bool vl);
		void SwitchFullscreen();

		vec2i GetSize();
		bool GetFullscreen();

		void* GetNativePtr();

	protected:
		virtual void EventCallback() = 0;

	protected:
		SDL_Window* mWndHandle;
		SDL_Event	mWndEvent;

		bool bIconified = false;

		static SDL_Window*		sSplashWndHandle;
		static SDL_Renderer*	sSplashWndRenderer;

	private:
		bool bFullscreen = false;
	};

	/// <summary>
	/// Exception for issues in window creation
	/// </summary>
	class GAMEENGINEAPI WindowException : public std::exception
	{
	public:
		WindowException(strgv msg);
		static void Throw(strgv msg);
		cstrg what() const noexcept override;

	private:
		strg mMsg;
	};
}
#endif