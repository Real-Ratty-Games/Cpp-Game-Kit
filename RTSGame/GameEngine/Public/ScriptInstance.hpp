/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef SCRIPTINSTANCE_HPP_
#define SCRIPTINSTANCE_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include "ScriptField.hpp"
#include <vector>

namespace GameEngine
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

		/// <summary>
		/// Returns front level fields in script
		/// </summary>
		/// <returns></returns>
		std::vector<ScriptField>& GetFields();

		/// <summary>
		/// Returns instance id
		/// </summary>
		/// <returns></returns>
		int ID();

	private:
		ScriptCore* pScriptCore;

		std::vector<ScriptField> mFields;
		int mID;
		strg mName;
	};
}
#endif