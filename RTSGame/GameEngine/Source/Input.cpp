/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Public/Input.hpp"
#include <SDL3/SDL_keyboard.h>
#include <SDL3/SDL_mouse.h>
#include <vector>

using namespace GameEngine;

/// Stores pressed keys/buttons
std::vector<KeyboardKey> _PressedKeyboardKeys;
std::vector<MouseButton> _PressedMouseButtons;

inline bool Input_CheckKeyboardKey(int key);
inline bool Input_CheckMouseButton(int button);

/*======================================================
	Keyboard
======================================================*/

/// <summary>
/// Check if key is held down
/// </summary>
/// <param name="key"></param>
/// <returns>True if key is held down</returns>
bool Keyboard::KeyDown(KeyboardKey key)
{
	return Input_CheckKeyboardKey((int)key);
}

/// <summary>
/// Check if key is not being held down
/// </summary>
/// <param name="key"></param>
/// <returns>True if key is up</returns>
bool Keyboard::KeyUp(KeyboardKey key)
{
	return !KeyDown(key);
}

/// <summary>
/// Check if key was pressed once
/// </summary>
/// <param name="key"></param>
/// <returns>True if key was only pressed once</returns>
bool Keyboard::KeyPressed(KeyboardKey key)
{
	const bool down = Input_CheckKeyboardKey((int)key);
	auto it = std::find(_PressedKeyboardKeys.begin(), _PressedKeyboardKeys.end(), key);
	const bool pressed = (it != _PressedKeyboardKeys.end());

	if (down && !pressed)
	{
		_PressedKeyboardKeys.push_back(key);
		return true;
	}
	else if (!down && pressed) _PressedKeyboardKeys.erase(it);
	return false;
}

/*======================================================
	Mouse
======================================================*/

/// <summary>
/// Check if button is held down
/// </summary>
/// <param name="button"></param>
/// <returns>True if button is held down</returns>
bool Mouse::ButtonDown(MouseButton button)
{
	return Input_CheckMouseButton((int)button);
}

/// <summary>
/// Check if button is not being held down
/// </summary>
/// <param name="button"></param>
/// <returns>True if button is up</returns>
bool Mouse::ButtonUp(MouseButton button)
{
	return !ButtonDown(button);
}

/// <summary>
/// Check if button was pressed once
/// </summary>
/// <param name="button"></param>
/// <returns>True if button was only pressed once</returns>
bool Mouse::ButtonPressed(MouseButton button)
{
	const bool down = Input_CheckMouseButton((int)button);
	auto it = std::find(_PressedMouseButtons.begin(), _PressedMouseButtons.end(), button);
	const bool pressed = (it != _PressedMouseButtons.end());

	if (down && !pressed)
	{
		_PressedMouseButtons.push_back(button);
		return true;
	}
	else if (!down && pressed) _PressedMouseButtons.erase(it);
	return false;
}

/// <summary>
/// Returns current mouse cursor location on screen
/// </summary>
/// <returns></returns>
vec2 Mouse::CursorLocation()
{
	float x, y;
	SDL_GetMouseState(&x, &y);
	return vec2(x, y);
}

/*======================================================
======================================================*/

/// <summary>
/// Returns true if keyboard key is held down
/// </summary>
/// <param name="key"></param>
/// <returns></returns>
bool Input_CheckKeyboardKey(int key)
{
	const bool* scode = SDL_GetKeyboardState(nullptr);
	return scode[key];
}

/// <summary>
/// Returns true if mouse button is held down
/// </summary>
/// <param name="button"></param>
/// <returns></returns>
bool Input_CheckMouseButton(int button)
{
	SDL_MouseButtonFlags flags = SDL_GetMouseState(nullptr, nullptr);
	return (flags == button);
}
