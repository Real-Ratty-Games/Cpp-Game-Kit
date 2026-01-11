/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Inc/Clock.hpp"
#include <SDL3/SDL.h>

using namespace GameEngine::Core;

Clock::Clock(double framerate)
{
	mDeltaTime = 0.0;
	mLastFrame = 0.0;
	mSpeed = 1.0;
	mAccumulatedTime = 0.0;
	mFreq = SDL_GetPerformanceFrequency();
	mFixedTime = (1.0 / framerate);
	bFirstTick = true;
}

/// <summary>
/// Advance counter
/// </summary>
void Clock::Tick()
{
	double currentFrame = static_cast<double>(SDL_GetPerformanceCounter()) / static_cast<double>(mFreq);

	if (bFirstTick)
	{
		bFirstTick = false;
		mLastFrame = currentFrame;
	}

	mDeltaTime = currentFrame - mLastFrame;
	mLastFrame = currentFrame;
	mDeltaTime *= mSpeed;

	// clamp delta to avoid big spikes
	if (mDeltaTime > 0.25) mDeltaTime = 0.25; // max 250ms frame

	mAccumulatedTime += mDeltaTime;
}

/// <summary>
/// Use like: while(Wait())
/// </summary>
/// <returns>True if frame passed</returns>
bool Clock::Wait()
{
	if (mAccumulatedTime >= mFixedTime)
	{
		mAccumulatedTime -= mFixedTime;
		return true;
	}
	return false;
}

/// <summary>
/// Set clock speed multiplier
/// </summary>
/// <param name="vl"></param>
void Clock::SetSpeed(double vl)
{
	mSpeed = vl;
}

/// <summary>
/// Set clock framerate
/// </summary>
/// <param name="framerate"></param>
void Clock::SetFramerate(double framerate)
{
	mFixedTime = (1.0 / framerate);
}
