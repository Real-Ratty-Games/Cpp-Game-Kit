/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef DRAWEXCEPTION_HPP_
#define DRAWEXCEPTION_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"

using namespace GameEngine::Core;

namespace GameEngine::Draw
{
	/// <summary>
	/// Exception for issues with rendering
	/// </summary>
	class GAMEENGINEAPI DrawException : public std::exception
	{
	public:
		DrawException(strgv msg);
		static void Throw(strgv msg);
		cstrg what() const noexcept override;

	private:
		strg mMsg;
	};
}
#endif