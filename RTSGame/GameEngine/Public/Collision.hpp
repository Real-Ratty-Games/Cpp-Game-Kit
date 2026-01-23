/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef COLLISION_HPP_
#define COLLISION_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include "Collider.hpp"

namespace GameEngine::Math::Collision
{
	GAMEENGINEAPI inline bool Intersect(const vec2& point,			const BoxCollider& box);
	GAMEENGINEAPI inline bool Intersect(const vec2& point,			const CircleCollider& circle);
	GAMEENGINEAPI inline bool Intersect(const BoxCollider& a,		const BoxCollider& b);
	GAMEENGINEAPI inline bool Intersect(const CircleCollider& a,	const CircleCollider& b);
	GAMEENGINEAPI inline bool Intersect(const BoxCollider& box,		const CircleCollider& circle);
}
#endif