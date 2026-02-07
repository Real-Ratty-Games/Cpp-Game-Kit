/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#include "../Include/WADFile.hpp"
#include "../Include/BigError.hpp"
#include <fstream>
#include <sstream>

using namespace GameEngine;

void WADFile::Open(strgv filepath)
{
	std::ifstream file(filepath.data(), std::ios::binary | std::ios::ate);
	std::streamsize size = file.tellg();
	file.seekg(0, std::ios::beg);

	std::vector<uint8> buffer(size);
	if (!file.read(reinterpret_cast<char*>(buffer.data()), size))
	{
		file.close();
		return;
	}
	file.close();

	strg buffer_str(buffer.begin(), buffer.end());
	std::istringstream stream(buffer_str, std::ios::binary);

	uint fileCnt = 0;
	stream.read(reinterpret_cast<char*>(&fileCnt), sizeof(fileCnt));

	for (uint i = 0; i < fileCnt; i++)
	{
		uint16 nameLength = 0;
		stream.read(reinterpret_cast<char*>(&nameLength), sizeof(nameLength));

		strg fileName(nameLength, '\0');
		stream.read(&fileName[0], nameLength);

		uint fileSize, fileOffset;
		uint8 fileType;
		stream.read(reinterpret_cast<char*>(&fileSize), sizeof(fileSize));
		stream.read(reinterpret_cast<char*>(&fileOffset), sizeof(fileOffset));
		stream.read(reinterpret_cast<char*>(&fileType), sizeof(fileType));

		// Read actual data
		std::istringstream sstream(buffer_str, std::ios::binary);
		sstream.seekg(static_cast<std::streampos>(fileOffset), std::ios::beg);
		std::vector<uint8> databuffer(fileSize);
		if (!sstream.read(reinterpret_cast<char*>(databuffer.data()), fileSize))
			throw BigError("Failed reading data here!");
		sstream.clear();

		WADData data((EWADFileDataType)fileType, databuffer);
		mData.insert(std::make_pair(fileName, data));
	}
	stream.clear();
	buffer.clear();
}

WADData* WADFile::Read(strgv itemname)
{
	strg name(itemname);
	if(mData.contains(name))
		return &mData[name];
	return nullptr;
}

std::unordered_map<strg, WADData>& WADFile::Data()
{
	return mData;
}

int WADFile::Size()
{
	return mData.size();
}

void WADFile::Close()
{
	mData.clear();
}
