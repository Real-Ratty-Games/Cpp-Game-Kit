/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Public/Sound.hpp"
#include <stdexcept>

using namespace GameEngine;

void Sound::LoadFromFile(SoundWav& obj, strgv filepath)
{
	if (obj.load(filepath.data()) != SoLoud::SO_NO_ERROR)
	{
		const strg errmsg = "Failed loading sound file: " + strg(filepath);
		throw new std::runtime_error(errmsg);
	}
}

void Sound::LoadFromMemory(SoundWav& obj, std::vector<uint8>& data)
{
	if (obj.loadMem(data.data(), data.size(), false, false) != SoLoud::SO_NO_ERROR)
		throw new std::runtime_error("Failed loading sound file from memory!");
}

void Sound::Initialize()
{
	mCore = new SoundCore();
	SoundResult err = mCore->init();
	if (err != SoLoud::SO_NO_ERROR)
		throw new std::runtime_error("Failed initializing sound engine!");
	mCore->set3dListenerUp(0.0f, 1.0f, 0.0f);
}

void Sound::Release()
{
	mCore->deinit();
	delete mCore;
	mCore = nullptr;
}

SoundCore* Sound::Core()
{
	return mCore;
}
