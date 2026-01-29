/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef VIEWPORT3D_HPP_
#define VIEWPORT3D_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"

namespace GameEngine
{
	class GAMEENGINEAPI Viewport3D
	{
	public:
		Viewport3D();
		void CreateView();
		const vec3& Forward() const;
		const vec3& Right() const;
		const mat4& View() const;
		const vec3& Up() const;

	public:
		float Fov;
		float Near;
		float Far;

		vec3 Eye;
		vec3 Target;
		vec3 SceneUp;

	private:
		mat4 mView;
		vec3 mForward;
		vec3 mRight;
		vec3 mUp;
	};

	class GAMEENGINEAPI ViewportOrtho3D : public Viewport3D
	{
	public:
		float Offset;
		float Bottom;
		float Right;
		float Left;
		float Top;
	};
}
#endif