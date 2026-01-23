/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef SPRITE_HPP_
#define SPRITE_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include "DrawData.hpp"

namespace GameEngine
{
	class GAMEENGINEAPI Sprite
	{
	public:
		Sprite(Texture* texture);
		void SetTexture(Texture* texture);
		Texture* GetTexture();

	public:
		vec2		RotationPivot;
		vec2		Size;

	private:
		Texture*	pTexture;
	};
}
#endif