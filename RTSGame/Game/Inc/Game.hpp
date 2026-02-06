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
#include <SpriteAnimation.hpp>

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
		void LoadShaders();
		void FreeShaders();

		void LoadData();
		void FreeData();

	private:
		GameWindow*		mWindow;
		Clock			mClock = Clock(120.0f);

		DrawSurface*	mBackBufferSurface;

		Shader			mSprite2DShader;
		Shader			mSprite2DIShader;
		Shader			mSprite2DAtlasShader;
		Shader			mSprite2DAtlasIShader;

		Viewport2D		mCamera;

		Texture			mFontTexture;
		Sprite*			mFontSprite;
		SpriteFont		mSpriteFont;

		Texture			mTestTexture;
		Sprite*			mTestSprite;
		SpriteAnimation mTestAnimation;
		SpriteAnimator	mTestAnimator;
	};
}
#endif