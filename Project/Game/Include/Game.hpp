/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef GAME_HPP_
#define GAME_HPP_
#include <SystemTypes.hpp>
#include <Program.hpp>
#include <Clock.hpp>
#include <Sound.hpp>
#include <Shader.hpp>
#include <Sprite.hpp>
#include <DrawSurface2D.hpp>
#include <DrawSurface3D.hpp>
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

	private:
		GameWindow*		mWindow;
		Clock			mClock = Clock(60.0f);

		Sound			mSound;

		Viewport2D		mCamera;
		Shader			mSprite2DShader;
		Shader			mSprite2DIShader;
		Shader			mSprite2DAtlasShader;
		Shader			mSprite2DAtlasIShader;

		DrawSurface2D*	mBackBufferSurface;
	};
}
#endif