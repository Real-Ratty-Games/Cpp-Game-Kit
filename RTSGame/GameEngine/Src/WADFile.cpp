/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "../Inc/WADFile.hpp"
#include <fstream>
#include <sstream>

using namespace GameEngine::Core;

/// <summary>
/// Open a wad file and load its contents into buffer
/// </summary>
/// <param name="filepath"></param>
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

	std::string buffer_str(buffer.begin(), buffer.end());
	std::istringstream stream(buffer_str, std::ios::binary);

	uint fileCnt = 0;
	stream.read(reinterpret_cast<char*>(&fileCnt), sizeof(fileCnt));

	for (uint i = 0; i < fileCnt; ++i)
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
			throw new WADException("Failed reading data here!");
		sstream.clear();

		WADData data((EWADFileDataType)fileType, databuffer);
		mData.insert(std::make_pair(fileName, data));
	}
	stream.clear();
	buffer.clear();
}

/// <summary>
/// Returns item in buffer
/// </summary>
/// <param name="itemname"></param>
/// <returns></returns>
WADData* WADFile::Read(strgv itemname)
{
	strg name(itemname);
	if(mData.contains(name))
		return &mData[name];
	return nullptr;
}

/// <summary>
/// Returns buffer pointer
/// </summary>
/// <returns></returns>
std::unordered_map<strg, WADData>& WADFile::Data()
{
	return mData;
}

/// <summary>
/// Returns item count
/// </summary>
/// <returns></returns>
int WADFile::Size()
{
	return mData.size();
}

/// <summary>
/// Dispose of items
/// </summary>
void WADFile::Close()
{
	mData.clear();
}

/*======================================================
	WADException
======================================================*/

WADException::WADException(strgv msg)
{
	mMsg = msg;
}

void WADException::Throw(strgv msg)
{
	throw WADException(msg);
}

cstrg WADException::what() const noexcept
{
	return mMsg.c_str();
}
