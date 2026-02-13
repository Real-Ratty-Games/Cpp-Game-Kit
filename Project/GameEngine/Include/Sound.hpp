/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef SOUND_HPP_
#define SOUND_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include <soloud/soloud.h>
#include <soloud/soloud_wav.h>
#include <vector>

namespace GameEngine
{
	typedef SoLoud::handle		SoundHandle;
	typedef SoLoud::AudioSource	SoundSrc;
	typedef SoLoud::Wav			SoundWav;
	typedef SoLoud::Soloud		SoundCore;
	typedef SoLoud::result		SoundResult;

	/// <summary>
	/// Manages audio
	/// </summary>
	class GAMEENGINEAPI Sound
	{
	public:
		static void LoadFromFile(SoundWav& obj, strgv filepath);
		static void LoadFromMemory(SoundWav& obj, std::vector<uint8>& data);

		void Initialize();
		void Release();

		SoundCore* Core();

	private:
		SoundCore* mCore;
	};
}
#endif