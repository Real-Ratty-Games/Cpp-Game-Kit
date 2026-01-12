/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Inc/ScriptText.hpp"
#include "../Inc/ScriptCore.hpp"
#include "../Inc/FileSystem.hpp"
#include "../Inc/ScriptException.hpp"
#include <lua/lua.hpp>
#include <lua/lauxlib.h>
#include <lua/lualib.h>

using namespace GameEngine::Script;

int ScriptText_DumpWriter(lua_State* L, const void* p, size_t sz, void* ud);

ScriptText::ScriptText(ScriptCore* scriptcore)
{
	pScriptCore = scriptcore;
}

/// <summary>
/// Load lua script from file
/// </summary>
/// <param name="filepath">file path</param>
/// <param name="bytecode">is the source file already in bytecode</param>
void ScriptText::LoadFromFile(strgv filepath, bool bytecode)
{
	if (!FileSystem::Exists(filepath))
	{
		const strg errmsg = "Failed loading script from file: " + strg(filepath);
		throw new ScriptException(errmsg);
	}
	mFilePath = filepath;

	if (bytecode)
		mData = FileSystem::ReadBinaryFile(filepath);
	else
	{
		lua_State* state = pScriptCore->State();

		if (luaL_loadfile(state, filepath.data()) != LUA_OK)
		{
			const strg errmsg = "Failed loading script from file: " + strg(filepath) + " -> " + strg(lua_tostring(state, -1));
			throw new ScriptException(errmsg);
			lua_pop(state, 1);
			return;
		}

		int status = lua_dump(state, ScriptText_DumpWriter, &mData, 1);  // 1 = strip debug info

		if (status != 0)
		{
			const strg errmsg = "Failed loading script from file: " + strg(filepath) + " -> " + strg(lua_tostring(state, -1));
			throw new ScriptException(errmsg);
			mData.clear();
			lua_pop(state, 1);
		}
	}
}

/// <summary>
/// Load lua script from memory
/// </summary>
/// <param name="data"></param>
void ScriptText::LoadFromMemory(strgv data)
{
	lua_State* state = pScriptCore->State();

	if (luaL_loadstring(state, data.data()) != LUA_OK)
	{
		lua_pop(state, 1);
		return;
	}

	int status = lua_dump(state, ScriptText_DumpWriter, &mData, 1);

	if (status != 0) mData.clear();
}

/// <summary>
/// Save compiled bytecode to file
/// </summary>
/// <param name="outpath"></param>
void ScriptText::DumpBytecode(strgv outpath)
{
	if (FileSystem::Exists(outpath))
		FileSystem::WriteBinaryFile(outpath, mData);
}

/// <summary>
/// Returns bytecode data
/// </summary>
/// <returns></returns>
std::vector<char>& ScriptText::Data()
{
	return mData;
}

/*======================================================
======================================================*/

/// <summary>
/// Dump writer for lua api
/// look at lua_Writer definition
/// </summary>
/// <param name="L"></param>
/// <param name="p"></param>
/// <param name="sz"></param>
/// <param name="ud"></param>
/// <returns></returns>
int ScriptText_DumpWriter(lua_State* L, const void* p, size_t sz, void* ud)
{
	std::vector<char>* ctx = static_cast<std::vector<char>*>(ud);
	const char* data = static_cast<const char*>(p);
	ctx->insert(ctx->end(), data, data + sz);
	return 0;
}
