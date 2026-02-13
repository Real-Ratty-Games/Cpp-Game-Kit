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
	/// <summary>
	/// Returns true if File/Path exists
	/// </summary>
	/// <param name="filepath"></param>
	/// <returns></returns>
	GAMEENGINEAPI bool				Exists(strgv filepath);
	GAMEENGINEAPI void				FileRemove(strgv filepath);

	/// <summary>
	/// 0 = full
	/// 1 = name
	/// 2 = extension
	/// </summary>
	/// <param name="dir"></param>
	/// <param name="nt"></param>
	/// <returns></returns>
	GAMEENGINEAPI  std::vector<strg>	FilesInDirectory(strgv dir, int nt);
	GAMEENGINEAPI  std::vector<strg>	SubDirectories(strgv dir);
	GAMEENGINEAPI  void					DirectoryCreate(strgv dir);
	GAMEENGINEAPI  void					DirectoryRemove(strgv dir);
	GAMEENGINEAPI  std::vector<char>	ReadBinaryFile(strgv filepath);
	GAMEENGINEAPI  void					WriteBinaryFile(strgv filepath, std::vector<char>& data);
	GAMEENGINEAPI  void					WriteTextFile(strgv filepath, strgv text);
}
#endif