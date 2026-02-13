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
	// 2D

	GAMEENGINEAPI bool Intersect(const vec2& point,			const RectCollider& rect);
	GAMEENGINEAPI bool Intersect(const vec2& point,			const CircleCollider& circle);
	GAMEENGINEAPI bool Intersect(const RectCollider& a,		const RectCollider& b);
	GAMEENGINEAPI bool Intersect(const CircleCollider& a,	const CircleCollider& b);
	GAMEENGINEAPI bool Intersect(const RectCollider& rect,	const CircleCollider& circle);

	// 3D

	GAMEENGINEAPI bool Intersect(const BoxCollider& a,		const BoxCollider& b);
	GAMEENGINEAPI bool Intersect(const vec3& point,			const BoxCollider& box);
	GAMEENGINEAPI bool Intersect(const vec3& point,			const SphereCollider& sphere);
	GAMEENGINEAPI bool Intersect(const SphereCollider& a,	const SphereCollider& b);
	GAMEENGINEAPI bool Intersect(const BoxCollider& box,	const SphereCollider& sphere);
}
#endif