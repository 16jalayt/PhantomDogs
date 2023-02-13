#include "Nancy/HIFF.h"
#include <Engine/Scene.h>
#include "Loader.h"
#include "HIFF Chunks/ACT/ACT.h"
#include "HIFF Chunks/SUM.h"

bool HIFF::Load_HIFF(std::string sceneName)
{
	std::ifstream inFile = Loader::getDataFile(sceneName);

	//Starts at end of file because | std::ios::ate
	long filesize = (long)inFile.tellg();
	//infile.fail() doesn't seem to work
	if (filesize == -1)
		return false;

	Scene_ptr newScene;

	inFile.seekg(0);

	std::string magic = readString(inFile, 4);

	if (magic != "DATA")
	{
		printf("Missing Data chunk in file: %s\n", sceneName.c_str());
		return false;
	}

	int chunkLenInt = readInt(inFile, true);
	//fails on newer games with flagevnt
	/*if (chunkLenInt != (filesize - 8))
	{
		printf("Invalid data chunk length in file: %s\n", sceneName.c_str());
		return false;
	}*/

	std::string subChunk = readString(inFile, 8);
	if (subChunk == "FLAGEVNT")
	{
		//Always 0?
		int flagevnt = readInt(inFile);

		std::string magic = readString(inFile, 4);

		if (magic != "DATA")
		{
			printf("Missing Data chunk in file: %s\n", sceneName.c_str());
			return false;
		}

		int chunkLenInt = readInt(inFile, true);

		subChunk = readString(inFile, 8);
	}
	if (subChunk == "SCENTSUM")
	{
		int sumLength = readInt(inFile, true);
		SUM::Parse(inFile, newScene, sceneName);
	}
	/*if (sumChunk == "SCENTSUM")
	{
		printf("Invalid Summery chunk in file: %s\n", sceneName.c_str());
		return false;
	}*/
	else
	{
		printf("Invalid data chunk:%s in file:%s\n", subChunk.c_str(), sceneName.c_str());
		return false;
	}

	newScene->sceneFile = sceneName;

	/////////////////////////////////////////////////

	while (inFile.tellg() != filesize && inFile.tellg() != EOF)
		//while (inFile.tellg() != filesize)
	{
		//If current byte is 0, HER made the count 1 off
		char testVal = readByte(inFile);
		if (testVal != 0)
			skipBytes(inFile, -1);

		long chunkStart = inFile.tellg();
		std::string actChunk = readString(inFile, 4);
		int chunkLen = readInt(inFile, true);

		//std::string actChunkDesc = readString(inFile, 48);
		//unsigned char chunkType = readByte(inFile);

		if (actChunk == "ACT")
			//if (chunkType == 25)
		{
			ACT::Parse(inFile, newScene, chunkLen);
		}
		else
		{
			//TODO: put chunk pos, skip bad chunk
			printf("Invalid chunk:%s in scene: %s  at: %ld\n", actChunk.c_str(), sceneName.c_str(), chunkStart);
			skipBytes(inFile, chunkLen);
		}
		//unsigned char readCheck = readByte(inFile);
		//skipBytes(inFile, -1);
	}

	ChangeScene(newScene);

	inFile.close();
	return true;
}