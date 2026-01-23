/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Public/Collision.hpp"
#include <algorithm>

using namespace GameEngine::Math;

/// <summary>
/// Point x Box collision test
/// </summary>
/// <param name="point"></param>
/// <param name="box"></param>
/// <returns></returns>
bool Collision::Intersect(const vec2& point, const BoxCollider& box)
{
	return point.X >= box.Location.X && point.X <= box.Location.X + box.Size.X &&
		point.Y >= box.Location.Y && point.Y <= box.Location.Y + box.Size.Y;
}

/// <summary>
/// Point x Circle collision test
/// </summary>
/// <param name="point"></param>
/// <param name="circle"></param>
/// <returns></returns>
bool Collision::Intersect(const vec2& point, const CircleCollider& circle)
{
	float dx = point.X - circle.Location.X;
	float dy = point.Y - circle.Location.Y;
	return (dx * dx + dy * dy) <= (circle.Radius * circle.Radius);
}

/// <summary>
/// Box x Box collision test
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
bool Collision::Intersect(const BoxCollider& a, const BoxCollider& b)
{
	bool cX = a.Location.X + a.Size.X >= b.Location.X &&
		b.Location.X + b.Size.X >= a.Location.X;
	bool cY = a.Location.Y + a.Size.Y >= b.Location.Y &&
		b.Location.Y + b.Size.Y >= a.Location.Y;
	return cX && cY;
}

/// <summary>
/// Circle x Circle collision test
/// </summary>
/// <param name="a"></param>
/// <param name="b"></param>
/// <returns></returns>
bool Collision::Intersect(const CircleCollider& a, const CircleCollider& b)
{
	float dx = a.Location.X - b.Location.X;
	float dy = a.Location.Y - b.Location.Y;
	float r = a.Radius + b.Radius;
	return (dx * dx + dy * dy) <= (r * r);
}

/// <summary>
/// Box x Circle collision test
/// </summary>
/// <param name="box"></param>
/// <param name="circle"></param>
/// <returns></returns>
bool Collision::Intersect(const BoxCollider& box, const CircleCollider& circle)
{
	float closestX = std::clamp(
		circle.Location.X,
		box.Location.X,
		box.Location.X + box.Size.X
	);

	float closestY = std::clamp(
		circle.Location.Y,
		box.Location.Y,
		box.Location.Y + box.Size.Y
	);

	float dx = circle.Location.X - closestX;
	float dy = circle.Location.Y - closestY;

	return (dx * dx + dy * dy) <= (circle.Radius * circle.Radius);
}
