/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef BILLBOARDRENDERER_HPP_
#define BILLBOARDRENDERER_HPP_
#include "SystemTypes.hpp"
#include "DrawData.hpp"
#include "Renderer.hpp"

namespace Tudo
{
	class GraphicsDevice;
	class DrawPipeline;
	class SpriteAnimator;
	class Texture;
	class Sprite;

	class BillboardRenderer : public Renderer
	{
	public:
		BillboardRenderer(GraphicsDevice& gdevice, DrawPipeline& pipeline);

		void DrawSprite(Sprite& sprite, const BillboardTransform& transform, bool cylindric);
	};
}
#endif