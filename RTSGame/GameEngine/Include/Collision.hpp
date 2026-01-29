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

	GAMEENGINEAPI inline bool Intersect(const vec2& point,			const RectCollider& rect);
	GAMEENGINEAPI inline bool Intersect(const vec2& point,			const CircleCollider& circle);
	GAMEENGINEAPI inline bool Intersect(const RectCollider& a,		const RectCollider& b);
	GAMEENGINEAPI inline bool Intersect(const CircleCollider& a,	const CircleCollider& b);
	GAMEENGINEAPI inline bool Intersect(const RectCollider& rect,	const CircleCollider& circle);

	// 3D

	GAMEENGINEAPI inline bool Intersect(const BoxCollider& a,		const BoxCollider& b);
	GAMEENGINEAPI inline bool Intersect(const vec3& point,			const BoxCollider& box);
	GAMEENGINEAPI inline bool Intersect(const vec3& point,			const SphereCollider& sphere);
	GAMEENGINEAPI inline bool Intersect(const SphereCollider& a,	const SphereCollider& b);
	GAMEENGINEAPI inline bool Intersect(const BoxCollider& box,		const SphereCollider& sphere);
}
#endif