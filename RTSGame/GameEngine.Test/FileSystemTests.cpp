/*======================================================
	Copyright (c) 2026 Real Ratty Games.
	This software is a trade secret.

	Revision history:
		* Created by Norbert Gerberg.
======================================================*/
#include "pch.h"
#include "CppUnitTest.h"
#include "SystemTypes.hpp"
#include "FileSystem.hpp"
#include "WADFile.hpp"
#include "WADMaker.hpp"
#include <vector>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace GameEngine::Core;

namespace GameEngineTest
{
	TEST_CLASS(FileSystemTests)
	{
	public:
		TEST_METHOD(ExistsTest)
		{
			Assert::IsTrue(FileSystem::Exists("GameEngine.dll"));
		}

		TEST_METHOD(FilesInDirectoryTest)
		{
			const uint64 expected = 3;
			std::vector<strg> list = FileSystem::FilesInDirectory("../../", 0);
			Assert::AreEqual(expected, list.size());
		}

		TEST_METHOD(WADTest)
		{
			const strg wadFileTestName = "_WADTestFile_.wad";

			std::unordered_map<strg, WADData> data;

			strg dtext = "This is test text!";
			std::vector<uint8> dbuffer(dtext.begin(), dtext.end());

			strg dtext2 = "I am suppose to be a sound file!";
			std::vector<uint8> dbuffer2(dtext2.begin(), dtext2.end());

			data.insert(std::make_pair("SomeTextFile", WADData(EWADFileDataType::RAW, dbuffer)));
			data.insert(std::make_pair("SomeSoundFile", WADData(EWADFileDataType::SOUND, dbuffer2)));

			WADMaker::MakeUnique(wadFileTestName, "", data);

			Assert::IsTrue(FileSystem::Exists(wadFileTestName));

			WADFile wadfile;
			wadfile.Open(wadFileTestName);

			WADData* dat1 = wadfile.Read("SomeTextFile");
			Assert::IsTrue(EWADFileDataType::RAW == dat1->Type);
			strg rstr = strg(dat1->Buffer.begin(), dat1->Buffer.end());
			Assert::IsTrue(dtext == rstr);

			WADData* dat2 = wadfile.Read("SomeSoundFile");
			Assert::IsTrue(EWADFileDataType::SOUND == dat2->Type);
			strg rstr2 = strg(dat2->Buffer.begin(), dat2->Buffer.end());
			Assert::IsTrue(dtext2 == rstr2);

			FileSystem::FileRemove(wadFileTestName);
		}
	};
}
