/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef GAME_HPP_
#define GAME_HPP_
#include <SystemTypes.hpp>
#include <Program.hpp>

using namespace GameEngine;
using namespace GameEngine::Core;

namespace MyGame
{
	class GameWindow;

	class GameProgram : public Program
	{
	protected:
		bool Initialize();
		void Tick();
		void Draw();
		void Cleanup();

	private:
		GameWindow* mWindow;
	};
}
#endif