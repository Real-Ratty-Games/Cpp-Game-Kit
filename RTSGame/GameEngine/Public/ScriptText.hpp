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
	/// Loading and compiling lua script
	/// </summary>
	class GAMEENGINEAPI ScriptText
	{
	public:
		ScriptText(ScriptCore* scriptcore);

		/// <summary>
		/// Load lua script from file
		/// </summary>
		/// <param name="filepath">file path</param>
		/// <param name="bytecode">is the source file already in bytecode</param>
		void LoadFromFile(strgv filepath, bool bytecode);
		void LoadFromMemory(strgv data);

		/// <summary>
		/// Save compiled bytecode to file
		/// </summary>
		/// <param name="outpath"></param>
		void DumpBytecode(strgv outpath);

		/// <summary>
		/// Returns bytecode data
		/// </summary>
		/// <returns></returns>
		std::vector<char>& Data();

	private:
		std::vector<char>	mData;
		strg				mFilePath;

		ScriptCore*			pScriptCore;
	};
}
#endif