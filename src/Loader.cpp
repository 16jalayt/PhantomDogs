#include "Utils.h"
#include "CIFF.h"
#include "Loader.h"
#include <Engine/Graphics.h>
#include <loguru.hpp>
#include "Scene.h"

GUI_ptr currentGUI;

bool Loader::Boot()
{
	//empty scene to not nullptr rendering at begining
	//Scene_ptr scene = Scene_ptr(new Scene("", "Boot"));
	//ChangeScene(Scene_ptr(new Scene("", "Boot", "")));
	loadScene("Boot");

	if (!CIFF::Load_Tree((char*)"DataFiles/CIFTREE.dat"))
		fatalError("Unable to load ciftree");
	//From danger by design. Split between cds
	//CIFF::Load_Tree((char*)"DataFiles/CIFTREE_.dat");
	CIFF::Load_Tree((char*)"DataFiles/PROMOTREE.DAT");
	//load cals, cifs, and loose hifs
	//load scene boot

	//Startup Flags:
	flags[1081 - 1000] = true;
	//DEBUG:
	//fixed flashlight
	flags[1146 - 1000] = true;
	//solved dog tile
	flags[1407 - 1000] = true;

	UIInit();

	//Torchlight
	//HIFF::Load_HIFF("4020");
//Puzzle Corrador
	//HIFF::Load_HIFF("4150");
	//tun stairs
	//loadScene("4069");
	loadScene("4604");
	// Tunnel by Kennel
	//HIFF::Load_HIFF("4141");

	return true;
}

void Loader::UIInit()
{
	//currentGUI = GUI_ptr(new GUIEngine());
	currentGUI = std::make_shared<GUI>();

	SDL_Rect CanvasRect = { 52, 18, 536, 292 };
	currentGUI->canvasRect = ScaleRect(CanvasRect, Engine::Config::globalScale);
	//currentGUI->canvasRect = { (int)(CanvasRect.x * Engine::Config::globalScale), (int)(CanvasRect.y * Engine::Config::globalScale), (int)(CanvasRect.w * Engine::Config::globalScale), (int)(CanvasRect.h * Engine::Config::globalScale) };
	currentGUI->canvas = SDL_Texture_ptr(SDL_CreateTexture(Engine::Graphics::renderer.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, currentGUI->canvasRect.w, currentGUI->canvasRect.h));

	Sprite_ptr frame = std::make_shared<Engine::Sprite>("DataFiles/CIFTREE/frame.png", 0, 0, RenderParent::window);
	currentGUI->AddSprite(frame);

	/*SDL_Rect uppermatte = ScaledRect_to_SDLRect(Scaled_Rect{ 0, 0, 800, 55 });
	currentGUI->AddRect(GUI_Rect{ uppermatte, 0, 0, 0 });

	currentGUI->canvasRect = { 0, uppermatte.h, 800, 536 };
	//currentGUI->canvasRect = { (int)(CanvasRect.x * GlobalScale), (int)(CanvasRect.y * GlobalScale), (int)(CanvasRect.w * GlobalScale), (int)(CanvasRect.h * GlobalScale) };
	currentGUI->canvas = SDL_Texture_ptr(SDL_CreateTexture(Graphics::renderer.get(), SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, currentGUI->canvasRect.w, currentGUI->canvasRect.h));

	SDL_Rect lowermatte = ScaledRect_to_SDLRect(Scaled_Rect{ 0, 536, 800, 600 });
	currentGUI->AddRect(GUI_Rect{ lowermatte, 0, 0, 0 });*/
}

void Loader::loadScene(int sceneName)
{
	Loader::loadScene(std::to_string(sceneName));
}

void Loader::loadScene(std::string sceneName)
{
	if (currentScene && sceneName == currentScene->sceneFile)
		ReloadScene();
	else
		_ChangeScene(sceneName);
}

std::ifstream Loader::loadTree(std::string treeName)
{
	return std::ifstream();
}

std::ifstream Loader::getDataFile(std::string sceneName)
{
	if (sceneName.empty())
		return std::ifstream();

	//TODO: get from tree not path
	//std::ifstream inFile;
	//NOTE: for testing bacause files are named the same
	/*if (oldUI)
		inFile = Utils::loadFile("DataFiles/CIFTREE/S" + sceneName + ".hiff");
	else
		inFile = Utils::loadFile("Ciftree/S" + sceneName + ".hiff");*/

	std::ifstream inFile = Utils::loadFile("DataFiles/CIFTREE/S" + sceneName + ".hiff");
	if (!inFile.fail()) {
		return inFile;
	}

	inFile = Utils::loadFile("Ciftree/S" + sceneName + ".hiff");
	if (!inFile.fail()) {
		return inFile;
	}

	LOG_F(ERROR, "Could not open HIFF file: %s", sceneName.c_str());
	return std::ifstream();
}

std::string Loader::getOVL(std::string ovlName)
{
	//TODO: get from tree not path
	if (ovlName.empty())
		return std::string();

	std::ifstream inFile = Utils::loadFile("DataFiles/CIFTREE/" + ovlName + ".png");
	if (!inFile.fail()) {
		inFile.close();
		return "DataFiles/CIFTREE/" + ovlName + ".png";
	}

	inFile = Utils::loadFile("Ciftree/" + ovlName + ".png");
	if (!inFile.fail()) {
		inFile.close();
		return "Ciftree/" + ovlName + ".png";
	}

	LOG_F(ERROR, "Could not open OVL file: %s", ovlName.c_str());
	return std::string();
}

//TODO: make faster? https://stackoverflow.com/questions/12774207/fastest-way-to-check-if-a-file-exists-using-standard-c-c11-14-17-c
//Note: prefers loose files
std::string Loader::getVideoPath(std::string backName)
{
	if (backName.empty())
		return std::string();

	std::ifstream inFile = Utils::loadFile("CDVideo/" + backName + ".png");
	if (!inFile.fail()) {
		inFile.close();
		return "CDVideo/" + backName + ".png";
	}

	inFile = Utils::loadFile("CDVideo/" + backName + ".bik");
	if (!inFile.fail()) {
		inFile.close();
		return "CDVideo/" + backName + ".bik";
	}

	inFile = Utils::loadFile("CDVideo/" + backName + ".avf");
	if (!inFile.fail()) {
		inFile.close();
		return "CDVideo/" + backName + ".avf";
	}

	inFile = Utils::loadFile("HDVideo/" + backName + ".png");
	if (!inFile.fail()) {
		inFile.close();
		return "HDVideo/" + backName + ".png";
	}

	inFile = Utils::loadFile("HDVideo/" + backName + ".bik");
	if (!inFile.fail()) {
		inFile.close();
		return "HDVideo/" + backName + ".bik";
	}

	inFile = Utils::loadFile("HDVideo/" + backName + ".avf");
	if (!inFile.fail()) {
		inFile.close();
		return "HDVideo/" + backName + ".avf";
	}

	inFile = Utils::loadFile("Video/" + backName + ".png");
	if (!inFile.fail()) {
		inFile.close();
		return "Video/" + backName + ".png";
	}

	inFile = Utils::loadFile("Video/" + backName + ".bik");
	if (!inFile.fail()) {
		inFile.close();
		return "Video/" + backName + ".bik";
	}

	inFile = Utils::loadFile("Video/" + backName + ".jpg");
	if (!inFile.fail()) {
		inFile.close();
		return "Video/" + backName + ".jpg";
	}

	inFile = Utils::loadFile("Video/" + backName + ".avf");
	if (!inFile.fail()) {
		inFile.close();
		return "Video/" + backName + ".avf";
	}

	inFile = Utils::loadFile("DataFiles/CIFTREE/" + backName + ".png");
	if (!inFile.fail()) {
		inFile.close();
		return "DataFiles/CIFTREE/" + backName + ".png";
	}

	LOG_F(ERROR, "Cannot find background: %s", backName.c_str());
	return std::string();
}

std::string Loader::getSoundPath(std::string soundName)
{
	//TODO: handle SILENCE
	if (soundName.empty())
		return std::string();

	std::ifstream inFile("HDSound/" + soundName + ".ogg");
	if (!inFile.fail()) {
		inFile.close();
		return "HDSound/" + soundName + ".ogg";
	}

	inFile = Utils::loadFile("CDSound/" + soundName + ".ogg");
	if (!inFile.fail()) {
		inFile.close();
		return "CDSound/" + soundName + ".ogg";
	}

	inFile = Utils::loadFile("HDSound/" + soundName + ".wav");
	if (!inFile.fail()) {
		inFile.close();
		return "HDSound/" + soundName + ".wav";
	}

	inFile = Utils::loadFile("CDSound/" + soundName + ".wav");
	if (!inFile.fail()) {
		inFile.close();
		return "CDSound/" + soundName + ".wav";
	}

	inFile = Utils::loadFile("HDSound/" + soundName + ".his");
	if (!inFile.fail()) {
		inFile.close();
		//LOG_F(ERROR, "HIS not supported yet!\n");
		return "HDSound/" + soundName + ".his";
		//return std::string();
	}

	inFile = Utils::loadFile("CDSound/" + soundName + ".his");
	if (!inFile.fail()) {
		inFile.close();
		//LOG_F(ERROR, "HIS not supported yet!\n");
		return "CDSound/" + soundName + ".his";
		//return std::string();
	}

	return std::string();
}