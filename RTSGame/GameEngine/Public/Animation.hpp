/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef ANIMATION_HPP_
#define ANIMATION_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include "Alarm.hpp"

namespace GameEngine
{
	/// <summary>
	/// Sprite Animation types
	/// </summary>
	enum class ESpriteAnimationStyle
	{
		NONE,			// 0 -> 1 -> 2 -> x
		LOOP,			// 0 -> 1 -> 2 -> 0 -> ..
		REVERSE,		// 0 -> 1 -> 2 -> 1 -> 0 -> x
		REVERSELOOP		// 0 -> 1 -> 2 -> 1 -> 0 -> 1 -> ..
	};

	/// <summary>
	/// Sprite animation properties
	/// </summary>
	struct SpriteAnimation
	{
		vec2					FrameSize;
		vec2					StartIndex;
		int64					Speed;				// in frames per second
		int						RowCount;			// how many frames in one row
		int						TotalFrameCount;	// how many frames in total
		ESpriteAnimationStyle	Style = ESpriteAnimationStyle::NONE;
	};

	/// <summary>
	/// Manages sprite animation
	/// </summary>
	class GAMEENGINEAPI SpriteAnimator
	{
	public:
		SpriteAnimator();
		void Play(SpriteAnimation* animation);
		void Replay();
		void Stop();
		void Pause(bool paused);
		bool IsFinished();
		void Tick();

		SpriteAnimation*	GetAnimation();
		vec2				GetCurrentIndex();

	private:
		int64 AdvanceFrame();

	private:
		SpriteAnimation*	pAnimation;

		Alarm				mAlarm;

		int					mCurrentFrame;
		vec2				mCurrentIndex;
		int					mFrameMul;
		bool				bAnimationFinished;
	};
}
#endif