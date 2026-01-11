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
		static void LoadFromFile(SoundWav& obj, strgv filepath);
		static void LoadFromMemory(SoundWav& obj, std::vector<uint8>& data);

		void Initialize();
		void Release();

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