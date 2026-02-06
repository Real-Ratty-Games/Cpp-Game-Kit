/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Inc/Game.hpp"
#include "../Inc/GameWindow.hpp"
#include <Renderer.hpp>
#include <Input.hpp>

using namespace MyGame;

static SpriteInstanceData	_SimpleTextData;
static SDL_Cursor*			_SdlCursor;

void GameProgram::OnResize(vec2i& size)
{
	mBackBufferSurface->OnResize(size);
}

bool GameProgram::Initialize()
{
	// create window
	Window::Initialize();
	Window::ShowSplashScreen();

	_SdlCursor = Window::LoadHardwareCursorImage("Data/Cursor.bmp");
	Window::SetHardwareCursorImage(_SdlCursor);

	mWindow = new GameWindow(this);
	mWindow->Create("My Game", 1280, 720, false);

	// init renderer
	if (!Renderer::Initialize(mWindow, DrawAPI::DIRECT3D11, true, MSAA::X16))
		return false;

	// setup shaders
	Shader::SetShaderDirectory("Data/Shaders");
	const strg result = Shader::CompileAllShaders("Data\\Development\\Shaders");
	LoadShaders();

	// create back buffer surface
	mBackBufferSurface = new DrawSurface(0, mWindow->GetNativePtr());

	// init camera
	mCamera.Size = mWindow->GetSize();

	LoadData();

	Transform2D transf;
	transf.Location = vec2(100, 100);
	transf.Scale = vec2(1);
	transf.Rotation = 0.0f;
	transf.ImageColor = Color(1);
	Renderer::PrepareSpriteFontText(mSpriteFont, transf, _SimpleTextData, "Hello, World!\nC++ is awesome!");

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
		mTestAnimator.Tick();

		if (Keyboard::KeyPressed(KeyboardKey::N1))
			mWindow->SwitchFullscreen();

		if (Keyboard::KeyPressed(KeyboardKey::ESCAPE))
			Quit();

		if (Keyboard::KeyPressed(KeyboardKey::SPACE))
			mTestAnimator.Replay();
		else if (Keyboard::KeyPressed(KeyboardKey::P))
			mTestAnimator.Pause(true);
		else if (Keyboard::KeyPressed(KeyboardKey::O))
			mTestAnimator.Pause(false);
	}
}

void GameProgram::Draw()
{
	Renderer::BeginDraw();
	if (!mWindow->IsIconified())
	{
		Renderer::BeginDrawSprite(mBackBufferSurface, mCamera);

		Renderer::SetActiveShader(&mSprite2DAtlasIShader);

		Renderer::DrawSpriteFontText(mSpriteFont, _SimpleTextData);

		Renderer::SetActiveShader(&mSprite2DAtlasShader);
		
		Transform2D transf;
		transf.Location = vec2(500, 300);
		transf.Rotation = 0;
		transf.Scale = vec2(1);
		Renderer::DrawSpriteAnimation(mTestSprite, transf, &mTestAnimator);

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

	Window::SetHardwareCursorImage(nullptr);
	SDL_DestroyCursor(_SdlCursor);

	if (mWindow != nullptr)
	{
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

	mSpriteFont.pSprite		= mFontSprite;
	mSpriteFont.GlyphSize	= vec2(18, 30);
	mSpriteFont.Glyphs		=
		"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"
		"ÄäÖöÜü"
		"0123456789"
		",;.:_-!?\"§$%&/()=*+~'#|<>²³{[]}\\";



	Renderer::LoadTextureFromFile(mTestTexture, "Data/TestAnimation.png", BGFX_SAMPLER_MIN_POINT |
		BGFX_SAMPLER_MAG_POINT |
		BGFX_SAMPLER_U_CLAMP |
		BGFX_SAMPLER_V_CLAMP, "TestAnimation", false);

	mTestSprite = new Sprite(&mTestTexture);

	mTestAnimation.FrameSize		= vec2(128);
	mTestAnimation.StartIndex		= vec2(3, 1);
	mTestAnimation.Speed			= 50;
	mTestAnimation.RowCount			= 4;
	mTestAnimation.TotalFrameCount	= 7;
	mTestAnimation.Style			= ESpriteAnimationStyle::REVERSELOOP;

	mTestAnimator.Play(&mTestAnimation);
}

void GameProgram::FreeData()
{
	if (mFontSprite != nullptr)
	{
		delete mFontSprite;
		mFontSprite = nullptr;
	}

	Renderer::FreeTexture(mFontTexture);

	if (mTestSprite != nullptr)
	{
		delete mTestSprite;
		mTestSprite = nullptr;
	}

	Renderer::FreeTexture(mTestTexture);
}
