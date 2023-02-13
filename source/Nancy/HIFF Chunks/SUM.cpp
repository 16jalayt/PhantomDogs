#include <Nancy/HIFF Chunks/SUM.h>
#include <string>
#include <Engine/utils.h>
#include <Engine/Button.h>
#include <Nancy/HIFF.h>
#include <Engine/Scene.h>

bool SUM::Parse(std::ifstream& inFile, Scene_ptr& scene, std::string sceneName)
{
	//Scene Description
	std::string sceneDesc = readString(inFile, 50);
	//scene->sceneName = sceneDesc;

	//printf("Loading scene: %s\n", sceneDesc.c_str());

	//The name of the scene background.
	//Same length as file name field in cifftree?
	std::string sceneBack = readString(inFile, 33);
	//scene->setBkg(sceneBack);

	scene = Scene_ptr(new Scene(sceneBack, sceneDesc, sceneName));

	//Ambient sound file
	std::string sound = readString(inFile, 33);

	//Scene specific sound channel
	int channel = readShort(inFile);

	//Loop. 0 infinite
	int loop = readInt(inFile);

	//Audio levels
	int chan1 = readShort(inFile);
	int chan2 = readShort(inFile);

	scene->AddMusic(sound, channel, loop, chan1, chan2);

	return true;
}