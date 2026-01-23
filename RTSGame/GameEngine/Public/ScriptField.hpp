/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef SCRIPTFIELD_HPP_
#define SCRIPTFIELD_HPP_
#include "SystemTypes.hpp"

namespace GameEngine
{
	/// <summary>
	/// Script field type
	/// </summary>
	enum class EScriptFieldType
	{
		OTHER,
		NUMBER,
		STRING,
		BOOL,
		METHOD
	};

	/// <summary>
	/// Script field properties
	/// </summary>
	struct ScriptField
	{
		EScriptFieldType	Type;
		strg				Name;
		strg				Value;
	};
}
#endif