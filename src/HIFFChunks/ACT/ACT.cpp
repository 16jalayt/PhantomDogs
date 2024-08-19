#include "ACT.h"
#include <random>
#include <string>

#include "../Dependency.h"
#include <Engine/Button.h>
#include <Engine/Utils.h>
#include <Engine/Config.h>
#include <loguru.hpp>
#include "../../Loader.h"
#include "../../Cursor.h"

bool ACT::Parse(std::ifstream& inFile, int chunkLen, int chunkStart)
{
	std::string actChunkDesc = readString(inFile, 48);
	unsigned char chunkType = readByte(inFile);

	//num times to execute. single=1 multi=2
	char HSExec = readByte(inFile);

	switch (chunkType)
	{
		//12
		//scene change from flags
	case 12:
	{
		LOG_F(INFO, "Processing ACT chunk:%u Desc:%s at:%d", chunkType, actChunkDesc.c_str(), chunkStart);

		//Scene to change to
		short changeTo = readShort(inFile);

		LOG_F(INFO, "Destination:%d", changeTo);

		skipBytes(inFile, 18);

		std::vector<Dependency> deps = parseDeps(inFile, chunkStart, chunkLen);

		if (!checkDeps(deps))
			break;

		//sceneChangeName = std::to_string(changeTo);
		//sceneChangeFlag = true;
		Loader::loadScene(changeTo);

		break;
	}

	//?
	//case 20:
		//Scene change with HS
	case 25:
	{
		//TODO: add x and y to log
		LOG_F(INFO, "Processing ACT chunk:%u Desc:%s at:%d", chunkType, actChunkDesc.c_str(), chunkStart);

		int cursorNumber = readShort(inFile);

		//scene to change to
		int changeTo = readShort(inFile);

		LOG_F(INFO, "Destination:%d", changeTo);

		//hot rect
		Scaled_Rect hot = Scaled_Rect{ readInt(inFile), readInt(inFile), readInt(inFile), readInt(inFile) };

		std::vector<Dependency> deps = parseDeps(inFile, chunkStart, chunkLen);

		if (!checkDeps(deps))
			break;

		Button_ptr hotZone = std::make_shared<Engine::Button>(hot, "");
		nextScene->AddHotzone(hotZone);
		hotZone->callback = [changeTo = changeTo]
			{
				//printf("lambda called\n");
				//TODO: IMPORTANT: lambda creates new thread and deletes object mid execution
				//find way to rejoin
				//set flag to change scene and have sceneproc load
				//sceneChangeName = std::to_string(changeTo);
				//sceneChangeFlag = true;
				Loader::loadScene(changeTo);
			};
		hotZone->hover_event = [cursorNumber = cursorNumber]
			{
				Cursor::setCursor(cursorNumber);
			};
		//Now handled in button
		//if (Config::debugHot)
			//hotZone->setDebug(true);
		//hotZone->visible(false);
		break;
	}
	//Movie playback
	case 53:
	{
		LOG_F(INFO, "Processing ACT chunk:%u Desc:%s at:%d", chunkType, actChunkDesc.c_str(), chunkStart);

		std::string video = readString(inFile, 0x42);
		//LOG_F(INFO, "  Video:%s", video.c_str());
		//skipBytes(inFile, chunkLen - 116);

		//unknown
		skipBytes(inFile, 0xdf);
		LOG_F(INFO, "  pos:%d", (int)inFile.tellg());
		Scaled_Rect pos = Scaled_Rect{ readInt(inFile), readInt(inFile), readInt(inFile), readInt(inFile) };
		//second pos can be different. Unknown purpose
		Scaled_Rect pos2 = Scaled_Rect{ readInt(inFile), readInt(inFile), readInt(inFile), readInt(inFile) };

		//Unknown. Zeros?
		skipBytes(inFile, 32);

		//LOG_F(INFO, "  pos:%d", (int)inFile.tellg());

		std::vector<Dependency> deps = parseDeps(inFile, chunkStart, chunkLen);

		if (!checkDeps(deps))
			break;

		std::string path = Loader::getVideoPath(video);
		Movie_ptr fmv = Movie_ptr(new Movie(path, pos.x, pos.y, false));
		nextScene->AddMovie(fmv);

		/*printf("Loading video:%s\n", video.c_str());
		std::string path = Loader::getVideoPath(video);
		Movie_ptr fmv = Movie_ptr(new Movie(path, 0, 0, false));
		nextScene->AddMovie(fmv);*/

		/*LOG_F(ERROR, "Before load bik");
		std::string path2 = Loader::getVideoPath("RKCINEC");
		Movie_ptr fmv2 = Movie_ptr(new Movie(path2, 0, 0, true));
		LOG_F(ERROR, "Before add bik");
		nextScene->AddMovie(fmv2);*/

		//Testing
		if (nextScene->fmvs.size() < 1)
		{
			/*std::string path = Loader::getVideoPath("CEM_TombStairs_ANIM");
			Movie_ptr fmv = Movie_ptr(new Movie(path, 0, 0, true));
			nextScene->AddMovie(fmv);*/
			//TODO: switch doesn't load next background after avf

			/*LOG_F(ERROR, "Before load bik");
			std::string path2 = Loader::getVideoPath("RKCINEC");
			Movie_ptr fmv2 = Movie_ptr(new Movie(path2, 0, 0, true));
			LOG_F(ERROR, "Before add bik");
			nextScene->AddMovie(fmv2);*/
		}
		//BinkPlayback_ptr menuFMV = make_BinkPlayback_s(new BinkPlayback());
		//menuFMV->OpenPaused(path, 0, 0, false);
		//nextScene->AddMovie(menuFMV);

		break;
	}
	//Scene Change with Frame
	/*case 16:
	{
		break;
	}*/
	//sfx
	/*case 158:
	{
		//num times to execute. single=1 multi=2
		char HSExec = readByte(inFile);

		int numSFX = readShort(inFile);
		std::vector<std::string> sfxNames;
		for (int i = 0; i < numSFX; i++)
		{
			sfxNames.push_back(readString(inFile, 33));
		}

		int channel = readShort(inFile);
		int channel = readShort(inFile);
		int channel = readShort(inFile);

		//AudioEngine levels
		int chan1 = readShort(inFile);
		int chan2 = readShort(inFile);

		//int?
		//int refScene

		//TODO:create jukebox like functionality in sound player

		break;
	}*/
	/*case 108:
	{
		printf("clear save not implemented\n");
		//Bad hack because lengh in hiff file is off by 1. HER's fault.
		skipBytes(inFile, chunkLen - 49);
		break;
	}*/
	/*case 211:
	{
		printf("Scopa card game not implemented\n");
		//Bad hack because lengh in hiff file is off by 1. HER's fault.
		skipBytes(inFile, chunkLen - 49);
		break;
	}*/
	//static overlay
	case 55:
	{
		LOG_F(INFO, "Processing ACT chunk:%u Desc:%s at:%d", chunkType, actChunkDesc.c_str(), chunkStart);

		//52 in newer games
		//printf("static overlay not implemented\n");

		std::string ovlImage = readString(inFile, 33);

		//TODO:parse deps func
		//?might not have deps like newer

		//?number of pixel copies from file
		int unknown1 = readShort(inFile);
		int zOrder = readShort(inFile);

		Scaled_Rect destRect = { readInt(inFile), readInt(inFile), readInt(inFile), readInt(inFile) };
		Scaled_Rect srcRect = { readInt(inFile), readInt(inFile), readInt(inFile), readInt(inFile) };

		std::vector<Dependency> deps = parseDeps(inFile, chunkStart, chunkLen);

		if (!checkDeps(deps))
			break;

		Sprite_ptr ovl = std::make_shared<Engine::Sprite>(Loader::getOVL(ovlImage).c_str(), destRect.x, destRect.y, RenderParent::canvas, srcRect);
		nextScene->AddSprite(ovl);

		//Bad hack because lengh in hiff file is off by 1.
		//TODO:This is because new act chunk needs to be even addr
		//A \0 is padding
		//skipBytes(inFile, chunkLen - 49);
		break;
	}
	//Event Flags with Cursor and HS
	//AT_EVENTFLAGS_CURSOR_HS
	case 98:
	{
		//TODO: incomplete implementation
		LOG_F(INFO, "Processing ACT chunk:%u Desc:%s at:%d", chunkType, actChunkDesc.c_str(), chunkStart);

		//Flag to update
		short flag = readShort(inFile);
		//truth
		int truth = readShort(inFile);

		//Cursor set to -1?
		LOG_F(INFO, "Cursor unknown pos:%d", (int)inFile.tellg());

		//Need cursor value somewhere
		//Currently unknown
		//skipBytes(inFile, 8);

		//Always -1?
		//TODO: assert
		int unknown1 = readShort(inFile);
		int unknown2 = readShort(inFile);

		int cursorNumber = readShort(inFile);

		int unknown3 = readShort(inFile);

		//one of the ones might be PUSH_SCENE=1

		//Frame hotspot is active in?
		//TODO: for rotating node
		int frame = readShort(inFile);
		Scaled_Rect hotZone = { readInt(inFile), readInt(inFile), readInt(inFile), readInt(inFile) };

		Button_ptr testbutton = std::make_shared<Engine::Button>(hotZone, "");
		nextScene->AddHotzone(testbutton);
		testbutton->callback = [flag = flag, truth = truth]
			{
				//TODO: make some sort of setFlag(flag);
				flags[flag - 1000] = truth;
				LOG_F(INFO, "set scene flag num: %d\n", flag);
				//sceneChangeName = currentScene->sceneFile;
				//sceneChangeFlag = true;
				Loader::loadScene(currentScene->sceneFile);
			};
		testbutton->hover_event = [cursorNumber = cursorNumber]
			{
				Cursor::setCursor(cursorNumber);
			};

		break;
	}
	//PUSH scene onto stack
	case 110:
	{
		LOG_F(INFO, "Processing ACT chunk:%u Desc:%s at:%d", chunkType, actChunkDesc.c_str(), chunkStart);

		//Unknown, status flag?
		char unknown = readByte(inFile);

		std::vector<Dependency> deps = parseDeps(inFile, chunkStart, chunkLen);

		if (!checkDeps(deps))
			break;

		//Notes on order
		//hs sets 1000
		//push and sc check dep 1000
		//Manual flag set does't have effect
		//Recheck conditions constantly?

		//Ghost dogs has 575ish EVs
		//Names hard coded into exe

		//Can't check in game. Change ev0, scene reloads and resets

		//Push current scene file name to scene stack
		prevScene = nextScene->sceneFile;

		break;
	}
	//POP scene from stack and transition
	case 111:
	{
		LOG_F(INFO, "Processing ACT chunk:%u Desc:%s at:%d", chunkType, actChunkDesc.c_str(), chunkStart);

		//Unknown, status flag?
		char unknown = readByte(inFile);

		std::vector<Dependency> deps = parseDeps(inFile, chunkStart, chunkLen);

		if (!checkDeps(deps))
			break;

		//Remove current scene and change to that scene
		//sceneChangeName = prevScene;
		//sceneChangeFlag = true;

		Loader::loadScene(prevScene);
		prevScene = "";

		break;
	}
	//Random sound CC
	case 151:
	{
		LOG_F(INFO, "Processing ACT chunk:%u Desc:%s at:%d", chunkType, actChunkDesc.c_str(), chunkStart);

		int numSounds = readShort(inFile);
		std::vector<std::string> sounds;
		for (int i = 0; i < numSounds; i++)
		{
			std::string sound = readString(inFile, 33);
			sounds.push_back(sound);
		}

		int channel = readShort(inFile);
		int loop = readInt(inFile);
		int volL = readShort(inFile);
		int volR = readShort(inFile);

		//next scene before sound ends
		bool waitOnSound = readByte(inFile);
		//Scene to change to
		int changeTo = readShort(inFile);

		int i = 0;
		//TODO: cc data
		do
		{
			//Length of closed caption data
			int length = readShort(inFile);
			skipBytes(inFile, length);
			//int unknown = readShort(inFile);
			//no idea why sometimes all cc data and sometimes one chunk
			if (length > 100)
				break;
			i++;
		} while (i < numSounds);

		//No idea
		int unknown = readShort(inFile);
		if (unknown != 0)
			skipBytes(inFile, -2);

		std::vector<Dependency> deps = parseDeps(inFile, chunkStart, chunkLen);

		if (!checkDeps(deps))
			break;

		std::mt19937 gen{ std::random_device{}() }; // generates random numbers
		std::uniform_int_distribution<std::size_t> dist(0, sounds.size() - 1); // maps the random number to [0..number of sounds]

		size_t index = dist(gen);
		std::string sound = sounds[index];
		nextScene->AddSound(sound, channel, loop, volL, volR);

		//sceneChangeName = std::to_string(changeTo);
		//sceneChangeFlag = true;
		Loader::loadScene(changeTo);

		break;
	}
	//Sound
	case 159:
	{
		LOG_F(INFO, "Processing ACT chunk:%u Desc:%s at:%d", chunkType, actChunkDesc.c_str(), chunkStart);

		std::string sound = readString(inFile, 33);
		LOG_F(INFO, "  Sound: %s", sound.c_str());

		int channel = readShort(inFile);
		int loop = readInt(inFile);
		int volL = readShort(inFile);
		int volR = readShort(inFile);

		//next scene before sound ends
		bool waitOnSound = readByte(inFile);
		//Scene to change to
		int changeTo = readShort(inFile);

		//Length of closed caption data
		int length = readShort(inFile);
		skipBytes(inFile, length);

		std::vector<Dependency> deps = parseDeps(inFile, chunkStart, chunkLen);

		//TODO: check deps not working
		if (!checkDeps(deps))
			break;

		LOG_F(INFO, "  valid");

		nextScene->AddSound(sound, channel, loop, volL, volR, changeTo);

		//sceneChangeName = std::to_string(changeTo);
		//sceneChangeFlag = true;

		// supposed to trigger after sound plays
		//Loader::loadScene(changeTo);

		break;
	}

	//Mouselight puzzle (Ghost dogs tunnel flashlight OVL)
	case 217:
	{
		LOG_F(INFO, "Processing ACT chunk:%u Desc:%s at:%d", chunkType, actChunkDesc.c_str(), chunkStart);

		//Name of the cave frame to show
		//Cave background is an OVL over top of a black background
		//So only shows up when flashlight cursor selected
		std::string ovlImage = readString(inFile, 33);

		skipBytes(inFile, 18);

		std::vector<Dependency> deps = parseDeps(inFile, chunkStart, chunkLen);

		if (!checkDeps(deps))
			break;

		Sprite_ptr ovl = std::make_shared<Engine::Sprite>(Loader::getOVL(ovlImage).c_str(), 0, 0);
		nextScene->AddSprite(ovl);

		Sprite_ptr mask = std::make_shared<Engine::Sprite>("data/lightmask.png", 0, 0);
		nextScene->AddSprite(mask);
		mask->isMask(true);

		break;
	}
	default:
	{
		LOG_F(ERROR, "**Invalid ACT chunk:%u Desc:%s in scene:%s at:%d", chunkType, actChunkDesc.c_str(), nextScene->sceneFile.c_str(), chunkStart);
		//int test = chunkLen - 49;
		skipBytes(inFile, chunkLen - 50);
		break;
	}
	}
	return true;
}