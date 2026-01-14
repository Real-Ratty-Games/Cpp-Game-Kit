/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef KEYBOARD_HPP_
#define KEYBOARD_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include "InputTypes.hpp"

using namespace GameEngine::Core;

namespace GameEngine::OS
{
	/// <summary>
	/// Keyboard input functions
	/// </summary>
	namespace Keyboard
	{
		GAMEENGINEAPI bool	KeyDown(KeyboardKey key);
		GAMEENGINEAPI bool	KeyUp(KeyboardKey key);
		GAMEENGINEAPI bool	KeyPressed(KeyboardKey key);
	}

	/// <summary>
	/// Mouse input functions
	/// </summary>
	namespace Mouse
	{
		GAMEENGINEAPI bool	ButtonDown(MouseButton button);
		GAMEENGINEAPI bool	ButtonUp(MouseButton button);
		GAMEENGINEAPI bool	ButtonPressed(MouseButton button);
		GAMEENGINEAPI vec2	CursorLocation();
	}
}
#endif