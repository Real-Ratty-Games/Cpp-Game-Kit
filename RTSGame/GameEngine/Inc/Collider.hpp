/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef COLLIDER_HPP_
#define COLLIDER_HPP_
#include "SystemTypes.hpp"
using namespace GameEngine::Core;

namespace GameEngine::Math
{
	/// <summary>
	/// 2D AABB body
	/// </summary>
	struct BoxCollider
	{
		vec2	Location;
		vec2	Size;
	};

	/// <summary>
	/// 2D Circle body
	/// </summary>
	struct CircleCollider
	{
		vec2	Location;
		float	Radius;
	};
}
#endif