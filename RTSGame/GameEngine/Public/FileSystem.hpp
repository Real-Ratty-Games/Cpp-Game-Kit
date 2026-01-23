/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef FILESYSTEM_HPP_
#define FILESYSTEM_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include <vector>

/// <summary>
/// Functions for managing system files and directories
/// </summary>
namespace GameEngine::FileSystem
{
	GAMEENGINEAPI inline bool				Exists(strgv filepath);
	GAMEENGINEAPI inline void				FileRemove(strgv filepath);
	GAMEENGINEAPI inline std::vector<strg>	FilesInDirectory(strgv dir, int nt);
	GAMEENGINEAPI inline std::vector<strg>	SubDirectories(strgv dir);
	GAMEENGINEAPI inline void				DirectoryCreate(strgv dir);
	GAMEENGINEAPI inline void				DirectoryRemove(strgv dir);
	GAMEENGINEAPI inline std::vector<char>	ReadBinaryFile(strgv filepath);
	GAMEENGINEAPI inline void				WriteBinaryFile(strgv filepath, std::vector<char>& data);
	GAMEENGINEAPI inline void				WriteTextFile(strgv filepath, strgv text);
}
#endif