/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Include/Sprite.hpp"
#include <stdexcept>

using namespace GameEngine;

Sprite::Sprite(Texture* texture)
{
	if (texture == nullptr)
		throw new std::runtime_error("Sprite creation failed: Texture cannot be nullptr!");
	pTexture	= texture;
	Size		= pTexture->Size;
}

void Sprite::SetTexture(Texture* texture)
{
	if (texture == nullptr)
		throw new std::runtime_error("Texture cannot be nullptr!");
	pTexture = texture;
}

Texture* Sprite::GetTexture()
{
	return pTexture;
}
