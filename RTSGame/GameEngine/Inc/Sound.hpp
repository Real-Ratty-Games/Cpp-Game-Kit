/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef SOUND_HPP_
#define SOUND_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>
#include <vector>

using namespace GameEngine::Core;

namespace GameEngine::OS
{
	typedef SoLoud::handle		SoundHandle;
	typedef SoLoud::AudioSource	SoundSrc;
	typedef SoLoud::Wav			SoundWav;
	typedef SoLoud::Soloud		SoundCore;
	typedef SoLoud::result		SoundResult;

	class GAMEENGINEAPI Sound
	{
	public:
		void Initialize();
		void Release();

		void LoadFromFile(SoundWav& obj, strgv filepath);
		void LoadFromMemory(SoundWav& obj, std::vector<uint8>& data);

		void Play(SoundWav& obj, SoundHandle& inst, float volume = 1.0f, bool paused = false, float pan = 0.0f, uint bus = 0);
		void Play3D(SoundWav& obj, SoundHandle& inst, vec3 location, vec3 velocity, float volume = 1.0f, bool paused = false, uint bus = 0);
		void SetLoop(SoundHandle& inst, bool vl);
		bool IsLooping(SoundHandle& inst);

		SoundCore* Core();

	private:
		SoundCore* mCore;
	};

	/// <summary>
	/// Exception for issues with sound engine
	/// </summary>
	class GAMEENGINEAPI SoundException : public std::exception
	{
	public:
		SoundException(strgv msg);
		static void Throw(strgv msg);
		cstrg what() const noexcept override;

	private:
		strg mMsg;
	};
}
#endif