/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef GAMEWINDOW_HPP_
#define GAMEWINDOW_HPP_
#include <SystemTypes.hpp>
#include <Window.hpp>
#include <Program.hpp>

using namespace GameEngine;
using namespace GameEngine::Core;
using namespace GameEngine::OS;

namespace MyGame
{
	class GameWindow : public Window
	{
	public:
		GameWindow(Program* program);

	protected:
		void EventCallback();

	private:
		Program* pProgram;
	};
}
#endif