/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef SHADER_HPP_
#define SHADER_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include "DrawData.hpp"
#include <unordered_map>

using namespace GameEngine::Core;

namespace GameEngine::Draw
{
	class GAMEENGINEAPI Shader
	{
	public:
		static void SetShaderDirectory(strgv dir);
		static strg CompileAllShaders(strgv dir);

		void Initialize(strgv shadername);
		void Release();

		void Submit(uint16 viewID, uint8 flags = 0, const bool depth = false);

		void InitUniform(strgv name, bgfx::UniformType::Enum type, uint16 nmb = 1);
		void SetUniform(strgv name, const void* vl, uint16 nmb = 1);
		void SetTexture(uint8 stage, strgv name, Texture& texture);

		bgfx::UniformHandle* GetUniform(strgv name);
		bgfx::ProgramHandle& GetProgramHandle();

	private:
		bgfx::ProgramHandle								mHandle;
		std::unordered_map<strg, bgfx::UniformHandle>	mUniforms;
	};
}
#endif