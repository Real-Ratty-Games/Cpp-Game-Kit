/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef WINDOW_HPP_
#define WINDOW_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include <SDL3/SDL.h>

namespace GameEngine
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

		/// <summary>
		/// Set hardware cursor image
		/// </summary>
		/// <param name="img">format must be bmp</param>
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

		/// <summary>
		/// Returns native OS window handle
		/// </summary>
		/// <returns></returns>
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
}
#endif