#pragma once

#include "GUI.h"
//load
//load video
//load audio
//load ovl
//boot   loads starting assets and starts first script

class Loader
{
public:
	static bool Boot();
	static void UIInit();
	static void loadScene(int sceneName);
	static void loadScene(std::string sceneName);
	static std::ifstream loadTree(std::string treeName);
	static std::ifstream getDataFile(std::string sceneName);
	static std::string getOVL(std::string ovlName);
	static std::string getVideoPath(std::string backName);
	static std::string getSoundPath(std::string soundName);
	//static GUI_ptr currentGUI;
};

extern GUI_ptr currentGUI;