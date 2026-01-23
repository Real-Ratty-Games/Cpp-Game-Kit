/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef GAMEPAD_HPP_
#define GAMEPAD_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include "InputTypes.hpp"
#include <vector>

class SDL_Gamepad;

namespace GameEngine
{
	/// <summary>
	/// Manages gamepad functionalities
	/// </summary>
	class GAMEENGINEAPI Gamepad
	{
    public:
        static void LoadConfig();
        bool        Connect(uint8 port);
        void        Disconnect();
        bool        IsConnected();
        bool        ButtonDown(GamepadButton button);
        bool        ButtonUp(GamepadButton button);
        bool        ButtonPressed(GamepadButton button);
        void        Rumble(uint16 left, uint16 right, uint time = 0);
        void        RumbleTriggers(uint16 left, uint16 right, uint time = 0);
        int16       Axis(GamepadAxis axis);

    private:
        SDL_Gamepad* mGamepadHandle = nullptr;
        std::vector<GamepadButton> mPressed;
	};
}
#endif