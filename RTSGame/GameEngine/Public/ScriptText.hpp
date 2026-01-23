/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef SCRIPT_HPP_
#define SCRIPT_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include <vector>

namespace GameEngine
{
	class ScriptCore;

	/// <summary>
	/// Loading and compiling lua scripts
	/// </summary>
	class GAMEENGINEAPI ScriptText
	{
	public:
		ScriptText(ScriptCore* scriptcore);
		void LoadFromFile(strgv filepath, bool bytecode);
		void LoadFromMemory(strgv data);
		void DumpBytecode(strgv outpath);
		std::vector<char>& Data();

	private:
		std::vector<char>	mData;
		strg				mFilePath;

		ScriptCore*			pScriptCore;
	};
}
#endif