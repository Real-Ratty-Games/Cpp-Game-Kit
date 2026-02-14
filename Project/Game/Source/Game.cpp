/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Include/Game.hpp"
#include "../Include/GameWindow.hpp"
#include <FileSystem.hpp>
#include <Renderer.hpp>
#include <Input.hpp>

using namespace MyGame;

static SDL_Cursor* _SdlCursor;

static SpriteInstanceData	_SimpleTextData;
static Texture _ftex;
static Sprite* _spriteFont;
static SpriteFont _ffont;

void GameProgram::OnResize(vec2i& size)
{
	mBackBufferSurface->OnResize(size);
}

bool GameProgram::Initialize()
{
	// create window
	Window::Initialize();
	Window::ShowSplashScreen();

    const strg cursorPath = FileSystem::GetResourcePath("Data/Cursor.bmp").string();
	_SdlCursor = Window::LoadHardwareCursorImage(cursorPath);
	Window::SetHardwareCursorImage(_SdlCursor);

	const vec2 resolution(1280, 720);

	mWindow = new GameWindow(this);
	mWindow->Create("My Game", resolution.X, resolution.Y, false);

	// init renderer
	DrawAPI dapi = DrawAPI::DIRECT3D11;
#if __APPLE__
	dapi = DrawAPI::METAL;
#endif

	if (!Renderer::Initialize(mWindow, dapi, true, MSAA::NONE))
		 return false;

	// setup shaders
	Shader::SetShaderDirectory("Data/Shaders");
    
    const strg shaderPath = FileSystem::GetResourcePath("Data\\Development\\Shaders").string();
	const strg result = Shader::CompileAllShaders(shaderPath);
	LoadShaders();

	// create back buffer surface
	mBackBufferSurface = new DrawSurface2D(0, resolution, mWindow->GetNativePtr());
    
	mCamera.Size = mWindow->GetSize();

	Window::DestroySplashScreen();
	mWindow->Show();
	return true;
}

void GameProgram::Tick()
{
	mWindow->PollEvent();

	if (Keyboard::KeyPressed(KeyboardKey::N1))
		mWindow->SwitchFullscreen();

	if (Keyboard::KeyPressed(KeyboardKey::ESCAPE))
		Quit();

	mClock.Tick();
	while (mClock.Wait())
	{
        // Logic here...
	}
}

void GameProgram::Draw()
{
	Renderer::BeginDraw();
	if (!mWindow->IsIconified())
	{
        Renderer::BeginDrawSprite(mBackBufferSurface, mCamera);
        
			Renderer::SetActiveShader(&mSprite2DAtlasIShader);
			Renderer::DrawSpriteFontText(_ffont, _SimpleTextData);

        Renderer::EndDrawSprite();
	}
	Renderer::EndDraw();
}

void GameProgram::Cleanup()
{
	if (mBackBufferSurface != nullptr)
	{
		mBackBufferSurface->Release();
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


	const strg fontTexPath = FileSystem::GetResourcePath("Data/Font.png").string();
	Renderer::LoadTextureFromFile(_ftex, fontTexPath, BGFX_SAMPLER_MIN_POINT |
		BGFX_SAMPLER_MAG_POINT |
		BGFX_SAMPLER_U_CLAMP |
		BGFX_SAMPLER_V_CLAMP, "Font", false);

	_spriteFont = new Sprite(&_ftex);

	_ffont.pSprite = _spriteFont;
	_ffont.GlyphSize = vec2(18, 30);
	_ffont.Glyphs =
		"AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPpQqRrSsTtUuVvWwXxYyZz"
		"ÄäÖöÜü"
		"0123456789"
		",;.:_-!?\"§$%&/()=*+~'#|<>²³{[]}\\";


	Transform2D transf;
	transf.Location = vec2(100, 100);
	transf.Scale = vec2(1);
	transf.Rotation = 0.0f;
	transf.ImageColor = Color(1);
	Renderer::PrepareSpriteFontText(_ffont, transf, _SimpleTextData, "This is now working on macOS!\nCool, right?");


}

void GameProgram::FreeShaders()
{
	mSprite2DShader.Release();
	mSprite2DIShader.Release();
	mSprite2DAtlasShader.Release();
	mSprite2DAtlasIShader.Release();

	delete _spriteFont;
	Renderer::FreeTexture(_ftex);
}
