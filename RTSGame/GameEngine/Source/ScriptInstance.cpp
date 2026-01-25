/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Public/ScriptInstance.hpp"
#include "../Public/ScriptCore.hpp"
#include "../Public/ScriptText.hpp"
#include <lua/lua.hpp>
#include <lua/lauxlib.h>
#include <lua/lualib.h>
#include <stdexcept>

using namespace GameEngine;

void ScriptInstance_ReadFields(lua_State* state, std::vector<ScriptField>& fields);
void ScriptInstance_FillValueType(lua_State* state, ScriptField& field);

ScriptInstance::ScriptInstance(ScriptCore* scriptcore, strgv instancename)
{
	pScriptCore = scriptcore;
	mID = LUA_NOREF;
	mName = instancename;
}

void ScriptInstance::Initialize(ScriptText* scripttext)
{
	lua_State* state = pScriptCore->State();

	lua_newtable(state);
	int envId = lua_gettop(state);

	lua_newtable(state);					// env, metatable
	lua_getglobal(state, "_G");				// env, metatable, _G
	lua_setfield(state, -2, "__index");		// env, metatable
	lua_setmetatable(state, envId);			// env with metatable

	// save instance address to access in script
	void** _ptr = (void**)lua_newuserdata(state, sizeof(ScriptInstance));
	*_ptr = this;
	lua_setfield(state, envId, "ThisScriptInstance");

	if (luaL_loadbuffer(state, scripttext->Data().data(), scripttext->Data().size(), mName.c_str()) != LUA_OK)
	{
		const strg errmsg = "Failed initializing script instance: " + mName + " -> " + strg(lua_tostring(state, -1));
		throw new std::runtime_error(errmsg);
		lua_pop(state, 1);
		return;
	}

	lua_pushvalue(state, envId);
	lua_setupvalue(state, -2, 1);

	if (lua_pcall(state, 0, 0, 0) != LUA_OK)
	{
		const strg errmsg = "Failed initializing script instance: " + mName + " -> " + strg(lua_tostring(state, -1));
		throw new std::runtime_error(errmsg);
		lua_pop(state, 1);
	}

	mID = luaL_ref(state, LUA_REGISTRYINDEX);

	// save front level fields
	lua_rawgeti(state, LUA_REGISTRYINDEX, mID);
	ScriptInstance_ReadFields(state, mFields);
}

void ScriptInstance::Release()
{
	if (mID != LUA_NOREF)
		luaL_unref(pScriptCore->State(), LUA_REGISTRYINDEX, mID);
}

void ScriptInstance::ExecuteMethod(ScriptField& field)
{
	if (field.Type != EScriptFieldType::METHOD)
	{
		throw new std::runtime_error("Field is not of type method!");
		return;
	}

	lua_State* state = pScriptCore->State();

	lua_rawgeti(state, LUA_REGISTRYINDEX, mID);
	lua_getfield(state, -1, field.Name.data());
	if (!lua_isfunction(state, -1))
	{
		lua_pop(state, 2);
		return;
	}

	lua_pushvalue(state, -2);
	lua_setupvalue(state, -2, 1);

	if (lua_pcall(state, 0, 0, 0) != LUA_OK)
	{
		const strg errmsg = "Error occured running method: " + field.Name + " -> " + strg(lua_tostring(state, -1));
		throw new std::runtime_error(errmsg);
		lua_pop(state, 1);
	}
	lua_pop(state, 1);
}

std::vector<ScriptField>& ScriptInstance::GetFields()
{
	return mFields;
}

int ScriptInstance::ID()
{
	return mID;
}

/*======================================================
======================================================*/

/// <summary>
/// Read fields in script and save into list
/// </summary>
/// <param name="state"></param>
/// <param name="fields"></param>
void ScriptInstance_ReadFields(lua_State* state, std::vector<ScriptField>& fields)
{
	lua_pushnil(state);

	if (!lua_istable(state, -2))
	{
		lua_pop(state, 1);
		return;
	}

	while (lua_next(state, -2) != 0)
	{
		const char* key = lua_tostring(state, -2);

		ScriptField property;
		property.Name = strg(key);
		ScriptInstance_FillValueType(state, property);
		fields.push_back(property);

		lua_pop(state, 1);
	}
	lua_pop(state, 1);
}

/// <summary>
/// Identifies and sets the fields correct type
/// </summary>
/// <param name="state"></param>
/// <param name="field"></param>
void ScriptInstance_FillValueType(lua_State* state, ScriptField& field)
{
	strg vl = "";
	EScriptFieldType type = EScriptFieldType::OTHER;

	if (lua_isboolean(state, -1))
	{
		type = EScriptFieldType::BOOL;
		vl = std::to_string(lua_toboolean(state, -1));
	}
	else if (lua_isnumber(state, -1))
	{
		type = EScriptFieldType::NUMBER;
		vl = std::to_string(lua_tonumber(state, -1));
	}
	else if (lua_isstring(state, -1))
	{
		type = EScriptFieldType::STRING;
		vl = strg(lua_tostring(state, -1));
	}
	else if (lua_isfunction(state, -1))
		type = EScriptFieldType::METHOD;

	field.Value = vl;
	field.Type = type;
}
