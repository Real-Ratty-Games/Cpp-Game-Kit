/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Inc/FileSystem.hpp"
#include <filesystem>
#include <fstream>

using namespace GameEngine::Core;

/// <summary>
/// Returns true if File/Path exists
/// </summary>
/// <param name="filepath"></param>
/// <returns></returns>
bool FileSystem::Exists(strgv filepath)
{
	return std::filesystem::exists(std::filesystem::path(filepath));
}

/// <summary>
/// Removes a file
/// </summary>
/// <param name="filepath"></param>
void FileSystem::FileRemove(strgv filepath)
{
	std::filesystem::remove(filepath);
}

/// <summary>
/// 0 = full
/// 1 = name
/// 2 = extension
/// </summary>
/// <param name="dir"></param>
/// <param name="nt"></param>
/// <returns></returns>
std::vector<strg> FileSystem::FilesInDirectory(strgv dir, int nt)
{
	if (Exists(dir))
	{
		std::vector<strg> rtVl;
		for (const auto& entry : std::filesystem::directory_iterator(dir))
		{
			if (entry.is_regular_file())
			{
				strg pb = entry.path().string();
				switch (nt)
				{
				case 1: { pb = entry.path().stem().string(); }break;
				case 2: { pb = entry.path().extension().string(); }break;
				}
				rtVl.push_back(pb);
			}
		}
		return rtVl;
	}
	return {};
}

/// <summary>
/// Returns list of sub directories
/// </summary>
/// <param name="dir"></param>
/// <returns></returns>
std::vector<strg> FileSystem::SubDirectories(strgv dir)
{
	if (Exists(dir))
	{
		std::vector<strg> rtVl;
		for (const auto& entry : std::filesystem::directory_iterator(dir))
		{
			if (entry.is_directory())
			{
				strg pb = entry.path().string();
				rtVl.push_back(pb);
			}
		}
		return rtVl;
	}
	return {};
}

/// <summary>
/// Creates a new directory on system
/// </summary>
/// <param name="dir"></param>
void FileSystem::DirectoryCreate(strgv dir)
{
	std::filesystem::create_directory(dir);
}

/// <summary>
/// Removes a directory from system with all its files
/// </summary>
/// <param name="dir"></param>
void FileSystem::DirectoryRemove(strgv dir)
{
	std::filesystem::remove_all(dir);
}

/// <summary>
/// Read a binary file
/// </summary>
/// <param name="filepath"></param>
/// <returns>buffer</returns>
std::vector<char> FileSystem::ReadBinaryFile(strgv filepath)
{
	std::vector<char> rtVl;

	std::ifstream File(filepath.data(), std::ios::in | std::ios::binary | std::ios::ate);
	std::streamsize size = File.tellg();
	rtVl.resize(size);

	File.seekg(0, std::ios::beg);
	File.read(rtVl.data(), size);
	File.close();

	return rtVl;
}

/// <summary>
/// Write a file in binary format
/// </summary>
/// <param name="filepath"></param>
/// <param name="data"></param>
void FileSystem::WriteBinaryFile(strgv filepath, std::vector<char>& data)
{
	std::ofstream File(filepath.data(), std::ios::binary);
	File.write(data.data(), data.size());
	File.close();
}
