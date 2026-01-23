/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef GAME_HPP_
#define GAME_HPP_
#include <SystemTypes.hpp>
#include <Program.hpp>
#include <Clock.hpp>
#include <DrawSurface.hpp>
#include <Shader.hpp>
#include <Sprite.hpp>

using namespace GameEngine;

namespace MyGame
{
	class GameWindow;

	class GameProgram : public Program
	{
	public:
		void OnResize(vec2i& size);

	protected:
		bool Initialize();
		void Tick();
		void Draw();
		void Cleanup();

	private:
		inline void LoadShaders();
		inline void FreeShaders();

		inline void LoadData();
		inline void FreeData();

	private:
		GameWindow*		mWindow;
		Clock			mClock = Clock(120.0f);

		DrawSurface*	mBackBufferSurface;
		DrawSurface*	mSurface2;

		Shader			mSprite2DShader;
		Shader			mSprite2DIShader;
		Shader			mSprite2DAtlasShader;
		Shader			mSprite2DAtlasIShader;

		Camera2D		mCamera;

		Texture			mFontTexture;
		Sprite*			mFontSprite;
	};
}
#endif