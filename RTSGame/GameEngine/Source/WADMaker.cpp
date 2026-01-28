/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Public/WADMaker.hpp"
#include "../Public/IniFile.hpp"
#include "../Public/FileSystem.hpp"
#include <filesystem>
#include <fstream>

using namespace GameEngine;

static std::vector<strg> WADMaker_GetFilesinDir(strgv filepath, bool on = false, bool saveExt = false);
static std::vector<uint8> WADMaker_GetFiletypesinDir(strgv filepath);

void WADMaker::Make(strgv inpath, strgv outloc, bool saveExt)
{
	const strg soutloc(outloc);
	strg infoFilepath(inpath);
	infoFilepath += "info.ini";

	if (!FileSystem::Exists(infoFilepath))
		return;

	IniFile ini;
	ini.Open(infoFilepath);
	strg outname = ini.Read("default", "vaultname", "UNKNOWN");
	outname += "." + ini.Read("default", "extension", "tv");
	ini.Close();

	std::vector<strg> files = WADMaker_GetFilesinDir(inpath);
	std::vector<strg> filenames = WADMaker_GetFilesinDir(inpath, true, saveExt);
	std::vector<uint8> filetypes = WADMaker_GetFiletypesinDir(inpath);
	std::vector<std::vector<uint8>> data;

	for (auto& it : files)
	{
		if (!FileSystem::Exists(it))
			return;

		std::ifstream file(it, std::ios::binary | std::ios::ate);
		std::streamsize size = file.tellg();
		file.seekg(0, std::ios::beg);

		std::vector<uint8> buffer(size);
		if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
			return;

		file.close();
		data.push_back(buffer);
	}

	std::ofstream OUT(soutloc + outname, std::ios::binary);

	uint fileCnt = filenames.size();
	OUT.write(reinterpret_cast<const char*>(&fileCnt), sizeof(fileCnt));

	uint currentOffset = sizeof(fileCnt);

	for (uint i = 0; i < fileCnt; ++i)
	{
		currentOffset += sizeof(uint16);
		currentOffset += filenames[i].size();
		currentOffset += sizeof(uint);
		currentOffset += sizeof(uint);
		currentOffset += sizeof(uint8);
	}

	for (uint i = 0; i < fileCnt; ++i)
	{
		uint16 nameLength = filenames[i].size();
		uint fileSize = data[i].size();
		uint fileOffset = currentOffset;
		uint8 fileType = filetypes[i];

		OUT.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
		OUT.write(filenames[i].data(), nameLength);
		OUT.write(reinterpret_cast<const char*>(&fileSize), sizeof(fileSize));
		OUT.write(reinterpret_cast<const char*>(&fileOffset), sizeof(fileOffset));
		OUT.write(reinterpret_cast<const char*>(&fileType), sizeof(fileType));

		currentOffset += fileSize;
	}

	for (auto& it : data)
		OUT.write(reinterpret_cast<const char*>(it.data()), it.size());

	OUT.close();
}

void WADMaker::MakeAll(strgv fileroot, strgv outloc, bool saveExt)
{
	std::vector<strg> totalpaths;
	for (auto& it : std::filesystem::recursive_directory_iterator(fileroot))
	{
		if (it.is_regular_file() && it.path().filename() == "info.ini")
			totalpaths.push_back(it.path().parent_path().string() + "\\");
	}

	for (auto& it : totalpaths) Make(it, outloc, saveExt);
}

void WADMaker::MakeUnique(strgv filename, strgv outloc, std::unordered_map<strg, WADData>& data)
{
	const strg soutloc(outloc);
	strg OUTPATH = soutloc + strg(filename);
	std::ofstream OUT(OUTPATH.data(), std::ios::binary);

	uint fileCnt = data.size();
	OUT.write(reinterpret_cast<const char*>(&fileCnt), sizeof(fileCnt));

	uint currentOffset = sizeof(fileCnt);

	for (auto& it : data)
	{
		currentOffset += sizeof(uint16);
		currentOffset += it.first.size();
		currentOffset += sizeof(uint);
		currentOffset += sizeof(uint);
		currentOffset += sizeof(uint8);
	}

	for (auto& it : data)
	{
		uint16 nameLength = it.first.size();
		uint fileSize = it.second.Buffer.size();
		uint fileOffset = currentOffset;
		uint8 fileType = (uint8)it.second.Type;

		OUT.write(reinterpret_cast<const char*>(&nameLength), sizeof(nameLength));
		OUT.write(it.first.data(), nameLength);
		OUT.write(reinterpret_cast<const char*>(&fileSize), sizeof(fileSize));
		OUT.write(reinterpret_cast<const char*>(&fileOffset), sizeof(fileOffset));
		OUT.write(reinterpret_cast<const char*>(&fileType), sizeof(fileType));

		currentOffset += fileSize;
	}

	for (auto& it : data)
		OUT.write(reinterpret_cast<const char*>(it.second.Buffer.data()), it.second.Buffer.size());

	OUT.close();
}

/*======================================================
======================================================*/

/// <summary>
/// Returns list of files in a directory that are of valid structure
/// </summary>
/// <param name="filepath"></param>
/// <param name="on"></param>
/// <param name="saveExt"></param>
/// <returns></returns>
std::vector<strg> WADMaker_GetFilesinDir(strgv filepath, bool on, bool saveExt)
{
	if (std::filesystem::exists(filepath))
	{
		std::vector<strg> rtVl;
		for (const auto& entry : std::filesystem::directory_iterator(filepath))
		{
			if (entry.is_regular_file())
			{
				strg pb = entry.path().string();

				if (pb.find("info.ini") != strg::npos) continue;

				if (on) pb = entry.path().stem().string();
				if (saveExt) pb = entry.path().filename().string();
				rtVl.push_back(pb);
			}
		}
		return rtVl;
	}
	return {};
}

/// <summary>
/// Returns list of file types in a directory that are of valid structure
/// </summary>
/// <param name="filepath"></param>
/// <returns></returns>
std::vector<uint8> WADMaker_GetFiletypesinDir(strgv filepath)
{
	std::vector<strg> image_ext = {
		"png", "PNG", "Png",
		"jpg", "JPG", "Jpg",
		"bmp", "BMP", "Bmp",
		"jpeg", "JPEG", "Jpeg",
		"dds", "DDS", "Dds",
		"gif", "GIF", "Gif",
		"tga", "TGA", "Tga"
	};

	std::vector<strg> sound_ext = {
		"wav", "WAV", "Wav",
		"mp3", "MP3", "Mp3",
		"aif", "AIF", "Aif",
		"mid", "MID", "Mid",
		"flac", "FLAC", "Flac",
		"m4a", "M4A", "M4a",
		"mp4", "MP4", "Mp4",
		"wma", "WMA", "Wma",
		"aac", "AAC", "Aac"
	};

	if (std::filesystem::exists(filepath))
	{
		std::vector<uint8> rtVl;
		for (const auto& entry : std::filesystem::directory_iterator(filepath))
		{
			if (entry.is_regular_file())
			{
				if (entry.path().string().find("info.ini") != strg::npos) continue;

				strg pb = entry.path().extension().string();
				pb = pb.erase(0, 1);

				uint8 vl = 0;
				if (std::find(image_ext.begin(), image_ext.end(), pb) != image_ext.end()) vl = 1;
				else if (std::find(sound_ext.begin(), sound_ext.end(), pb) != sound_ext.end()) vl = 2;
				else vl = 0;

				rtVl.push_back(vl);
			}
		}
		return rtVl;
	}
	return {};
}
