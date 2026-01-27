/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef EULERROTATION_HPP_
#define EULERROTATION_HPP_
#include "SystemTypes.hpp"

namespace GameEngine
{
	struct EulerRotation
	{
		float Yaw;
		float Pitch;
		float Roll;

		EulerRotation()
		{
			Yaw = Pitch = Roll = 0.0f;
		}

		EulerRotation(float vl)
		{
			Yaw = Pitch = Roll = vl;
		}

		EulerRotation(float yaw, float pitch, float roll)
		{
			Yaw = yaw;
			Pitch = pitch;
			Roll = roll;
		}
	};
}
#endif