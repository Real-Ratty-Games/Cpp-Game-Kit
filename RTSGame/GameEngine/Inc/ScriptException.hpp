/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef SCRIPTEXCEPTION_HPP_
#define SCRIPTEXCEPTION_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"

using namespace GameEngine::Core;

namespace GameEngine::Script
{
	/// <summary>
	/// Exception for issues with scripting
	/// </summary>
	class GAMEENGINEAPI ScriptException : public std::exception
	{
	public:
		ScriptException(strgv msg);
		static void Throw(strgv msg);
		cstrg what() const noexcept override;

	private:
		strg mMsg;
	};
}
#endif