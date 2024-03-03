#pragma once
#include <fstream>

#include "Scene.h"
#include <Engine/GUIEngine.h>
#include <Engine/SDL_ptr.h>
#include <vector>

class GUI : public GUIEngine
{
public:
	void Draw();
private:
	void drawCheatSheet();

	bool cheatSheetOpen = true;
};

using GUI_ptr = std::shared_ptr<GUI>;
