/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#ifndef WADFILE_HPP_
#define WADFILE_HPP_
#include "API.hpp"
#include "SystemTypes.hpp"
#include <vector>
#include <unordered_map>
#include <stdexcept>

namespace GameEngine
{
	enum class EWADFileDataType : uint8
	{
		RAW		= 0,
		TEXTURE = 1,
		SOUND	= 2
	};

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

	class GAMEENGINEAPI WADFile
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

	class GAMEENGINEAPI WADException : public std::exception
	{
	public:
		WADException(strgv msg);
		static void Throw(strgv msg);
		cstrg what() const noexcept override;

	private:
		strg mMsg;
	};
}
#endif