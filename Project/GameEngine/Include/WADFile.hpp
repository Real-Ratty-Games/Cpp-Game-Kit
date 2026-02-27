/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	Created by Norbert Gerberg.
======================================================*/
#ifndef WADFILE_HPP_
#define WADFILE_HPP_
#include "SystemTypes.hpp"
#include <vector>
#include <unordered_map>

namespace GameEngine
{
	/// <summary>
	/// Data types for wad file entry
	/// </summary>
	enum class EWADFileDataType : uint8
	{
		RAW		= 0,
		TEXTURE = 1,
		SOUND	= 2,
		MODEL	= 3
	};

	/// <summary>
	/// WAD file entry
	/// </summary>
	struct WADData
	{
	public:
		EWADFileDataType	Type;
		std::vector<uint8>	Buffer;

		WADData()
		{
			Type = EWADFileDataType::RAW;
		}

		WADData(EWADFileDataType type, std::vector<uint8> buffer)
		{
			Type = type;
			Buffer = buffer;
		}
	};

	/// <summary>
	/// Read data from a wad file
	/// </summary>
	class WADFile
	{
	public:
		void								Open(strgv filepath);
		WADData*							Read(strgv itemname);
		std::unordered_map<strg, WADData>&	Data();
		int									Size();
		void								Close();

	private:
		std::unordered_map<strg, WADData>	mData;
	};
}
#endif