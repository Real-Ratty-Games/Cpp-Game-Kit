/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Inc/Sound.hpp"

using namespace GameEngine::OS;

void Sound::Initialize()
{
	mCore = new SoundCore();
	SoundResult err = mCore->init();
	if (err != SoLoud::SO_NO_ERROR)
		throw new SoundException("Failed initializing sound engine!");
	mCore->set3dListenerUp(0.0f, 1.0f, 0.0f);
}

void Sound::Release()
{
	mCore->deinit();
	delete mCore;
	mCore = nullptr;
}

void Sound::LoadFromFile(SoundWav& obj, strgv filepath)
{
	if (obj.load(filepath.data()) != SoLoud::SO_NO_ERROR)
	{
		const strg errmsg = "Failed loading sound file: " + strg(filepath);
		throw new SoundException(errmsg);
	}
}

void Sound::LoadFromMemory(SoundWav& obj, std::vector<uint8>& data)
{
	if (obj.loadMem(data.data(), data.size(), false, false) != SoLoud::SO_NO_ERROR)
		throw new SoundException("Failed loading sound file from memory!");
}

void Sound::Play(SoundWav& obj, SoundHandle& inst, float volume, bool paused, float pan, uint bus)
{
	inst = mCore->play(obj, volume, pan, paused, bus);
}

void Sound::Play3D(SoundWav& obj, SoundHandle& inst, vec3 location, vec3 velocity, float volume, bool paused, uint bus)
{
	inst = mCore->play3d(obj, location.X, location.Y, location.Z, velocity.X, velocity.Y, velocity.Z, volume, paused, bus);
}

void Sound::SetLoop(SoundHandle& inst, bool vl)
{
	mCore->setLooping(inst, vl);
}

bool Sound::IsLooping(SoundHandle& inst)
{
	return mCore->getLooping(inst);
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
