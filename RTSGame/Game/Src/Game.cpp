/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Inc/Game.hpp"
#include "../Inc/GameWindow.hpp"
#include <Renderer.hpp>
#include <Input.hpp>

using namespace GameEngine::OS;
using namespace GameEngine::Draw;

using namespace MyGame;

void GameProgram::OnResize(vec2i& size)
{
	mBackBufferSurface->OnResize(size);
}

bool GameProgram::Initialize()
{
	// create window
	Window::Initialize();
	Window::ShowSplashScreen();

	Window::SetHardwareCursorImage("Data/Cursor.bmp");

	mWindow = new GameWindow(this);
	mWindow->Create("My Game", 1280, 720, false);

	// init renderer
	if (!Renderer::Initialize(mWindow, DrawAPI::DIRECT3D11, true, MSAA::X16))
		return false;

	// setup shaders
	Shader::SetShaderDirectory("Data/Shaders");
	// const strg result = Shader::CompileAllShaders("Data\\Development\\Shaders");
	LoadShaders();

	// create back buffer surface
	mBackBufferSurface = new DrawSurface(0, mWindow->GetNativePtr());

	// init camera
	mCamera.Size = mWindow->GetSize();

	LoadData();

	Window::DestroySplashScreen();
	mWindow->Show();
	return true;
}

void GameProgram::Tick()
{
	mWindow->PollEvent();

	mClock.Tick();
	while (mClock.Wait())
	{
		if (Keyboard::KeyPressed(KeyboardKey::N1))
			mWindow->SwitchFullscreen();

		if (Keyboard::KeyPressed(KeyboardKey::ESCAPE))
			Quit();
	}
}

void GameProgram::Draw()
{
	Renderer::BeginDraw();
	if (!mWindow->IsIconified())
	{

		Renderer::BeginDrawSprite(mBackBufferSurface, mCamera);

		Renderer::SetActiveShader(&mSprite2DAtlasIShader);

		Transform2D transf;
		transf.Location		= vec2(100, 100);
		transf.Scale		= vec2(1);
		transf.Rotation		= 0.0f;
		transf.ImageColor	= Color(1);
		Renderer::DrawSpriteFontText(mFontSprite, transf, vec2(18, 30), "Hello, World!\nC++ is awesome!");

	}
	Renderer::EndDraw();
}

void GameProgram::Cleanup()
{
	FreeData();

	if (mBackBufferSurface != nullptr)
	{
		delete mBackBufferSurface;
		mBackBufferSurface = nullptr;
	}

	FreeShaders();
	Renderer::Release();

	if (mWindow != nullptr)
	{
		mWindow->Release();
		delete mWindow;
		mWindow = nullptr;
	}
	Window::Release();
}

void GameProgram::LoadShaders()
{
	// default sprite shader
	mSprite2DShader.Initialize("Sprite2D");
	mSprite2DShader.InitUniform("s_texColor", bgfx::UniformType::Sampler);
	mSprite2DShader.InitUniform("color", bgfx::UniformType::Vec4);

	// default sprite instancing shader
	mSprite2DIShader.Initialize("Sprite2DI");
	mSprite2DIShader.InitUniform("s_texColor", bgfx::UniformType::Sampler);

	// default sprite atlas shader
	mSprite2DAtlasShader.Initialize("Sprite2DAtlas");
	mSprite2DAtlasShader.InitUniform("s_texColor", bgfx::UniformType::Sampler);
	mSprite2DAtlasShader.InitUniform("atlasInfo", bgfx::UniformType::Vec4, 2);
	mSprite2DAtlasShader.InitUniform("color", bgfx::UniformType::Vec4);

	// default sprite atlas instancing shader
	mSprite2DAtlasIShader.Initialize("Sprite2DAtlasI");
	mSprite2DAtlasIShader.InitUniform("s_texColor", bgfx::UniformType::Sampler);
	mSprite2DAtlasIShader.InitUniform("atlasInfo", bgfx::UniformType::Vec4, 2);
}

void GameProgram::FreeShaders()
{
	mSprite2DShader.Release();
	mSprite2DIShader.Release();
	mSprite2DAtlasShader.Release();
	mSprite2DAtlasIShader.Release();
}

void GameProgram::LoadData()
{
	Renderer::LoadTextureFromFile(mFontTexture, "Data/Font.png", BGFX_SAMPLER_MIN_POINT |
		BGFX_SAMPLER_MAG_POINT |
		BGFX_SAMPLER_U_CLAMP |
		BGFX_SAMPLER_V_CLAMP, "Font", false);

	mFontSprite = new Sprite(&mFontTexture);
}

void GameProgram::FreeData()
{
	if (mFontSprite != nullptr)
	{
		delete mFontSprite;
		mFontSprite = nullptr;
	}

	Renderer::FreeTexture(mFontTexture);
}
