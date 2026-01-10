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
		bool GAMEENGINEAPI			KeyDown(KeyboardKey key);
		bool GAMEENGINEAPI			KeyUp(KeyboardKey key);
		bool GAMEENGINEAPI			KeyPressed(KeyboardKey key);
	}

	/// <summary>
	/// Mouse input functions
	/// </summary>
	namespace Mouse
	{
		bool GAMEENGINEAPI			ButtonDown(MouseButton button);
		bool GAMEENGINEAPI			ButtonUp(MouseButton button);
		bool GAMEENGINEAPI			ButtonPressed(MouseButton button);
		vec2 GAMEENGINEAPI			CursorLocation();
	}
}
#endif