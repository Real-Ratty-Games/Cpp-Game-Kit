/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef CLOCK_HPP_
#define CLOCK_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"

namespace GameEngine::Core
{
	/// <summary>
	/// Managing fixed timestep
	/// </summary>
	class GAMEENGINEAPI Clock
	{
	public:
		Clock(double framerate);
		void Tick();
		bool Wait();
		void SetSpeed(double vl);
		void SetFramerate(double framerate);

	private:
		double	mDeltaTime;
		double	mLastFrame;
		double	mSpeed;
		double	mFixedTime;
		double	mAccumulatedTime;
		uint64	mFreq;
		bool	bFirstTick;
	};
}
#endif