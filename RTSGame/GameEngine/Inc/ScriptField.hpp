/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef SCRIPTFIELD_HPP_
#define SCRIPTFIELD_HPP_
#include "SystemTypes.hpp"

using namespace GameEngine::Core;

namespace GameEngine::Script
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