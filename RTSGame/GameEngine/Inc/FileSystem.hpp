/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef FILESYSTEM_HPP_
#define FILESYSTEM_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include <vector>

/// <summary>
/// Functions for managing system files and directories
/// </summary>
namespace GameEngine::Core::FileSystem
{
	inline GAMEENGINEAPI bool				Exists(strgv filepath);
	inline GAMEENGINEAPI void				FileRemove(strgv filepath);
	inline GAMEENGINEAPI std::vector<strg>	FilesInDirectory(strgv dir, int nt);
	inline GAMEENGINEAPI std::vector<strg>	SubDirectories(strgv dir);
	inline GAMEENGINEAPI void				DirectoryCreate(strgv dir);
	inline GAMEENGINEAPI void				DirectoryRemove(strgv dir);
}
#endif