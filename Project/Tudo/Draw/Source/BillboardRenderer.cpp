/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "BillboardRenderer.hpp"
#include "Transformation.hpp"
#include "GraphicsDevice.hpp"
#include "DrawPipeline.hpp"
#include "DrawSurface.hpp"
#include "Texture.hpp"
#include "Shader.hpp"

#include "Sprite.hpp"

using namespace Tudo;

BillboardRenderer::BillboardRenderer(GraphicsDevice& gdevice, DrawPipeline& pipeline) : Renderer(gdevice, pipeline) {}

void BillboardRenderer::DrawSprite(Sprite& sprite, const BillboardTransform& transform, bool cylindric)
{
	Shader* shader = pPipeline->GetActiveShader();

	bgfx::setState(TUDO_RENDERER_MESH_DEFAULT_STATE);
	bgfx::setVertexBuffer(0, pGDevice->GetQuadVertexHandle());

	mat4 mdl = mat4::Identity();
	mdl = Math::Translate(mdl, transform.Location, false);
	pGDevice->SetModelTransform(mdl);

	vec4 tvec = vec4(transform.Scale.X, transform.Scale.Y, sprite.RotationPivot.X, sprite.RotationPivot.Y);
	pGDevice->SetShaderUniform("u_transform", tvec.Ptr());

	vec4 fvec = vec4(cylindric ? 1 : 0, 0, 0, 0);
	pGDevice->SetShaderUniform("u_flags", fvec.Ptr());

	pGDevice->SetShaderTexture(0, "s_texColor", *sprite.GetTexture());

	vec4 col = transform.ImageColor.ToVec();
	pGDevice->SetShaderUniform("u_color", col.Ptr());

	shader->Submit(pPipeline->GetActiveDrawSurface()->ViewID(), TUDO_RENDERER_MESH_DEFAULT_DISCARD, true);
}
