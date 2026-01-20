/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Inc/Sprite.hpp"
#include "../Inc/DrawException.hpp"

using namespace GameEngine::Draw;

Sprite::Sprite(Texture* texture)
{
	if (texture == nullptr)
		throw new DrawException("Sprite creation failed: Texture cannot be nullptr!");
	pTexture	= texture;
	Size		= pTexture->Size;
}

void Sprite::SetTexture(Texture* texture)
{
	if (texture == nullptr)
		throw new DrawException("Texture cannot be nullptr!");
	pTexture = texture;
}

Texture* Sprite::GetTexture()
{
	return pTexture;
}
