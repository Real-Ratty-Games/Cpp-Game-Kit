/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Inc/Sound.hpp"

using namespace GameEngine::OS;

/// <summary>
/// Load sound data from file
/// </summary>
/// <param name="obj">sound instance</param>
/// <param name="filepath"></param>
void Sound::LoadFromFile(SoundWav& obj, strgv filepath)
{
	if (obj.load(filepath.data()) != SoLoud::SO_NO_ERROR)
	{
		const strg errmsg = "Failed loading sound file: " + strg(filepath);
		throw new SoundException(errmsg);
	}
}

/// <summary>
/// Load sound from memory
/// </summary>
/// <param name="obj">sound instance</param>
/// <param name="data"></param>
void Sound::LoadFromMemory(SoundWav& obj, std::vector<uint8>& data)
{
	if (obj.loadMem(data.data(), data.size(), false, false) != SoLoud::SO_NO_ERROR)
		throw new SoundException("Failed loading sound file from memory!");
}

/// <summary>
/// Create sound engine core
/// </summary>
void Sound::Initialize()
{
	mCore = new SoundCore();
	SoundResult err = mCore->init();
	if (err != SoLoud::SO_NO_ERROR)
		throw new SoundException("Failed initializing sound engine!");
	mCore->set3dListenerUp(0.0f, 1.0f, 0.0f);
}

/// <summary>
/// Delete sound engine core
/// </summary>
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

/*======================================================
	SoundException
======================================================*/

SoundException::SoundException(strgv msg)
{
	mMsg = msg;
}

void SoundException::Throw(strgv msg)
{
	throw SoundException(msg);
}

cstrg SoundException::what() const noexcept
{
	return mMsg.c_str();
}
