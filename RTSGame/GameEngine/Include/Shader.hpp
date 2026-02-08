/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef SHADER_HPP_
#define SHADER_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include "DrawData.hpp"
#include <unordered_map>

namespace GameEngine
{
	/// <summary>
	/// Manages a shader
	/// </summary>
	class GAMEENGINEAPI Shader
	{
	public:
		static void SetShaderDirectory(strgv dir);
		static strg CompileAllShaders(strgv dir);

		void Initialize(strgv shadername);
		void Release();

		void Submit(uint16 viewID, uint8 flags = 
			BGFX_DISCARD_INDEX_BUFFER
			| BGFX_DISCARD_VERTEX_STREAMS
			// | BGFX_DISCARD_BINDINGS
			| BGFX_DISCARD_STATE
			| BGFX_DISCARD_TRANSFORM
			, const bool depth = true);

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