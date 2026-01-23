/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Public/Animation.hpp"
#include "../Public/Sprite.hpp"

using namespace GameEngine;

SpriteAnimator::SpriteAnimator()
{
	pAnimation = nullptr;
	mCurrentFrame = 0;
	mCurrentIndex = vec2(0);
	mFrameMul = 1;
	bAnimationFinished = false;
	mAlarm.PushModule("AdvanceFrame", GAMEENGINE_ALARM_BIND(SpriteAnimator::AdvanceFrame), GAMEENGINE_ALARM_DISABLE);
}

/// <summary>
/// Play animation
/// </summary>
/// <param name="animation"></param>
void SpriteAnimator::Play(SpriteAnimation* animation)
{
	pAnimation = animation;
	Replay();
}

/// <summary>
/// Replay animation from beginning
/// </summary>
void SpriteAnimator::Replay()
{
	mCurrentFrame = 0;
	mFrameMul = 1;
	mCurrentIndex = pAnimation->StartIndex;
	bAnimationFinished = false;
	Pause(false);
	mAlarm.SetModuleCount("AdvanceFrame", pAnimation->Speed);
}

/// <summary>
/// Stop animation
/// </summary>
void SpriteAnimator::Stop()
{
	mAlarm.SetModuleCount("AdvanceFrame", GAMEENGINE_ALARM_DISABLE);
}

/// <summary>
/// Pause animation
/// </summary>
/// <param name="paused"></param>
void SpriteAnimator::Pause(bool paused)
{
	mAlarm.SetModulePaused("AdvanceFrame", paused);
}

/// <summary>
/// Returns true if animation has finished
/// Does not check while looping
/// </summary>
/// <returns></returns>
bool SpriteAnimator::IsFinished()
{
	return bAnimationFinished;
}

/// <summary>
/// Advance animation
/// </summary>
void SpriteAnimator::Tick()
{
	mAlarm.Tick();
}

/// <summary>
/// Returns pointer to current animation
/// </summary>
/// <returns></returns>
SpriteAnimation* SpriteAnimator::GetAnimation()
{
	return pAnimation;
}

/// <summary>
/// Returns current index for atlas rendering
/// </summary>
/// <returns></returns>
vec2 SpriteAnimator::GetCurrentIndex()
{
	return mCurrentIndex;
}

/// <summary>
/// Advance a frame and manage animation style
/// </summary>
/// <returns></returns>
int64 SpriteAnimator::AdvanceFrame()
{
	const int	totalframes = pAnimation->TotalFrameCount - 1;
	const float maxrow		= (pAnimation->StartIndex.X + pAnimation->RowCount - 1);

	mCurrentFrame += mFrameMul;
	if (mFrameMul == 1 && mCurrentFrame > totalframes)
	{
		switch (pAnimation->Style)
		{
		case ESpriteAnimationStyle::NONE:
		{
			mCurrentFrame = totalframes;
			bAnimationFinished = true;
			return GAMEENGINE_ALARM_DISABLE;
		}break;
		case ESpriteAnimationStyle::LOOP:
		{
			mCurrentFrame = 0;
			mCurrentIndex = pAnimation->StartIndex;
			return pAnimation->Speed;
		}
		default:
		{
			mCurrentFrame	= totalframes;
			mFrameMul		= -1;
		}break;
		}
	}

	if (mFrameMul == -1 && mCurrentFrame <= 0)
	{
		if (pAnimation->Style == ESpriteAnimationStyle::REVERSELOOP)
		{
			mFrameMul = 1;
			mCurrentFrame += mFrameMul;

			mCurrentIndex.X += mFrameMul;
			if (mCurrentIndex.X > maxrow)
			{
				mCurrentIndex.X = pAnimation->StartIndex.X;
				mCurrentIndex.Y++;
			}
			return pAnimation->Speed;
		}
		else
		{
			mCurrentFrame = 0;
			bAnimationFinished = true;
			return GAMEENGINE_ALARM_DISABLE;
		}
	}

	mCurrentIndex.X += mFrameMul;
	if (mFrameMul == 1 && mCurrentIndex.X > maxrow)
	{
		mCurrentIndex.X = pAnimation->StartIndex.X;
		mCurrentIndex.Y++;
	}
	else if (mCurrentIndex.X < pAnimation->StartIndex.X)
	{
		mCurrentIndex.X = maxrow;
		mCurrentIndex.Y--;
	}
	return pAnimation->Speed;
}
