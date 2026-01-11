/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef SCRIPTINSTANCE_HPP_
#define SCRIPTINSTANCE_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include "ScriptField.hpp"
#include <vector>

using namespace GameEngine::Core;

namespace GameEngine::Script
{
	class ScriptCore;
	class ScriptText;

	/// <summary>
	/// Instance that can execute logic
	/// </summary>
	class GAMEENGINEAPI ScriptInstance
	{
	public:
		ScriptInstance(ScriptCore* scriptcore, strgv instancename);
		void Initialize(ScriptText* scripttext);
		void Release();
		void ExecuteMethod(ScriptField& field);
		std::vector<ScriptField>& GetFields();
		int ID();

	private:
		ScriptCore* pScriptCore;

		std::vector<ScriptField> mFields;
		int mID;
		strg mName;
	};
}
#endif