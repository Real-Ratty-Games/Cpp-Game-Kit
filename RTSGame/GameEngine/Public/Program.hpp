/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef PROGRAM_HPP_
#define PROGRAM_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"

namespace GameEngine
{
	class GAMEENGINEAPI Program
	{
	public:
		void Run();
		void Quit(bool vl = true);

	protected:
		virtual bool Initialize() = 0;
		virtual void Tick() = 0;
		virtual void Draw() = 0;
		virtual void Cleanup() = 0;

	private:
		bool bQuit = false;
	};
}
#endif