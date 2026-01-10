/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef COLLISION_HPP_
#define COLLISION_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include "Collider.hpp"

using namespace GameEngine::Core;

namespace GameEngine::Math::Collision
{
	inline bool GAMEENGINEAPI Intersect(const vec2& point,			const BoxCollider& box);
	inline bool GAMEENGINEAPI Intersect(const vec2& point,			const CircleCollider& circle);
	inline bool GAMEENGINEAPI Intersect(const BoxCollider& a,		const BoxCollider& b);
	inline bool GAMEENGINEAPI Intersect(const CircleCollider& a,	const CircleCollider& b);
	inline bool GAMEENGINEAPI Intersect(const BoxCollider& box,		const CircleCollider& circle);
}
#endif