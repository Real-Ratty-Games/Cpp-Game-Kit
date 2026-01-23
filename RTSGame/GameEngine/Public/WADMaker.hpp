/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef WADMAKER_HPP_
#define WADMAKER_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include "WADFile.hpp"
#include <unordered_map>

namespace GameEngine::WADMaker
{
	GAMEENGINEAPI void Make(strgv inpath, strgv outloc, bool saveExt = false);
	GAMEENGINEAPI void MakeAll(strgv fileroot, strgv outloc, bool saveExt = false);
	GAMEENGINEAPI void MakeUnique(strgv filename, strgv outloc, std::unordered_map<strg, WADData>& data);
}
#endif