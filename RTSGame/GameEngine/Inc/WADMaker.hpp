/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef WADMAKER_HPP_
#define WADMAKER_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include "WADFile.hpp"
#include <unordered_map>

namespace GameEngine::WADMaker
{
	void GAMEENGINEAPI Make(strgv inpath, strgv outloc, bool saveExt = false);
	void GAMEENGINEAPI MakeAll(strgv fileroot, strgv outloc, bool saveExt = false);
	void GAMEENGINEAPI MakeUnique(strgv filename, strgv outloc, std::unordered_map<strg, WADData>& data);
}
#endif