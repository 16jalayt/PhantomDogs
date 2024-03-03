#define SDL_MAIN_HANDLED
//disable for insecure c functions and a warning about cxx17 standard
#pragma warning( disable : 4996 )

#define LOGURU_IMPLEMENTATION 1
#define LOGURU_WITH_STREAMS 1
#define LOGURU_FILENAME_WIDTH 15
#define LOGURU_THREADNAME_WIDTH 13
#include <loguru.hpp>

#ifdef __APPLE__
#include <unistd.h>
#endif

#ifdef __SWITCH__
#include <switch.h>
#endif

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
//#include <SDL2/SDL_ttf.h>
#include <SDL2/SDL2_framerate.h>
#include <SDL2/SDL2_rotozoom.h>

#include "globals.h"
#include "Engine\Utils.h"
#include "Engine\Graphics.h"
#include "Engine\Sprite.h"
#include "Engine\SDL_ptr.h"
#include "Engine\Button.h"
#include "Engine\Config.h"
#include "Scene.h"
#include "Loader.h"
#include "Utils.h"
#include "Engine\GUI.h"

#include "Engine\Cursor.h"
#include "Engine\Audio.h"
#include <Engine\SapphireApp.h>
#include <imgui.h>

int main(int argc, char** argv)
{
	Config::parse(argc, argv);
	Utils::initLog(argc, argv);

	SapphireApp_ptr app = std::make_unique<SapphireApp>("PhantomDogs", "A reimplementation of Nancy Drew 7");
	//if (!app)
	//{
		//printf("\nUnable to start engine\n");
		//quit();
	//}

	//Test loading screen
	//SDL_Delay(2000);

	//Sprite_ptr frame = std::make_shared<Sprite>("DataFiles/CIFTREE/frame.png", 0, 0, RenderParent::window);
	//frame->setPos(SDL_Rect{ 0,0,(int)(frame->getWidth() * GlobalScale), (int)(frame->getHeight() * GlobalScale) });
	// Scene::ChangeScene(Scene_ptr(new Scene("Video/TUN_KenZR.png")));

	Loader::Boot();

	// render text as texture
	//SDL_Rect helloworld_rect = { 0, SCREEN_HEIGHT - 36, 0, 0 };
	//SDL_Texture_ptr helloworld_tex = graphics->render_text("Hello, world!", graphics->getFont().get(), { 255, 255, 255, 0 }, &helloworld_rect);

	//BinkPlayback_ptr bkFMV = BinkPlayback_ptr(new BinkPlayback());
	//bkFMV->OpenBackground("Video/TUT_DeskCU_TXT_BG.bik");

	//BinkPlayback_ptr menuFMV = BinkPlayback_ptr(new BinkPlayback());
	//BinkPlayback_ptr menuFMV = make_BinkPlayback_s(new BinkPlayback());
	//menuFMV->Open("Video/RKCINEC.bik", 0, 0, true);

	//16 bits per sample mono
	//_dataBuffers uint8_t
	//Mix_Chunk chunk = new byte[20];

	// loop variables
	int exit_requested = 0;
	int wait = 25;
	SDL_Event event;
	bool toggle = true;
	int scenenum = 0;
	bool check = false;

	//IMGUI does not like being in a dll
	ImGui::SetCurrentContext(currentGUI->imCtx);
#if !defined(__SWITCH__) && !defined(__APPLE__)
	ImGuiIO& io = ImGui::GetIO();
#endif

	/*std::vector<BinkPlayback_ptr> test;
	std::string path = Loader::getVideoPath("YogiCine_");
	BinkPlayback_ptr menuFMV = make_BinkPlayback_s(new BinkPlayback());
	menuFMV->Open(path, 0, 0, false);
	test.push_back(menuFMV);
	//nextScene->AddMovie(menuFMV);*/

	/*Mix_Chunk* gMedium = Mix_LoadWAV("HDSound/NGD198.ogg");
	//Mix_Chunk* gMedium = Mix_LoadWAV("data/pop1.wav");
	if (gMedium == NULL)
	{
		printf("Failed to load medium sound effect! SDL_mixer Error: %s\n", Mix_GetError());
	}
	Mix_PlayChannel(-1, gMedium, 0);*/

#ifdef __SWITCH__
	while (!exit_requested && appletMainLoop())
#else
	while (!exit_requested)
#endif
	{
		//IMGUI does not like being in a dll
		ImGui::SetCurrentContext(currentGUI->imCtx);

		if (sceneReloadFlag)
		{
			ReloadScene();
		}
		if (sceneChangeFlag)
		{
			sceneChangeFlag = false;
			//Used as scene control variable
			//flags[0] = false;
			//HIFF::Load_HIFF(sceneChangeName);
			_LoadScene(sceneChangeName);
		}

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				exit_requested = 1;
				break;
			}

			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(Graphics::window.get()))
			{
				exit_requested = 1;
				break;
			}

			currentGUI->EventProc(event);

			switch (event.type)
			{
				// use joystick
#ifdef __SWITCH__
			case SDL_JOYBUTTONDOWN:
				switch (event.jbutton.button)
				{
					/*case KEY_LSTICK_UP:
						if (wait > 0)
							wait--;
						break;
					case KEY_LSTICK_DOWN:
						if (wait < 100)
							wait++;
						break;*/
				case KEY_MINUS:
					LOG_F(ERROR, "\nShutting down engine\n");
					exit_requested = 1;
					break;
				}
#endif
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE)
				{
					LOG_F(ERROR, "\nShutting down engine\n");
					exit_requested = 1;
					break;
				}
#if !defined(__SWITCH__) && !defined(__APPLE__)
				if (io.WantCaptureKeyboard)
#endif
					break;
			case SDL_MOUSEBUTTONDOWN:
			case SDL_FINGERDOWN:
#if !defined(__SWITCH__) && !defined(__APPLE__)
				if (!io.WantCaptureMouse)
#endif
					//LOG_F(ERROR, "FingerDown");
					currentScene->EventProc(event);
				//LOG_F(ERROR, "Touch at: %d,%d\n", event.tfinger.x, event.tfinger.y);
				break;
			case SDL_MOUSEMOTION:
			case SDL_FINGERMOTION:
#if !defined(__SWITCH__) && !defined(__APPLE__)
				if (!io.WantCaptureMouse)
				{
#endif
					//LOG_F(ERROR, "Fingermotion");
					//TODO: explicitly set to system cursor for IMGUI?
					Cursor::CursorChanged = false;
					currentScene->EventProc(event);
#if !defined(__SWITCH__) && !defined(__APPLE__)
				}
#endif
				break;

				/*switch (event.key.keysym.sym)
				{
					case SDLK_ESCAPE:
						LOG_F(ERROR, "\nShutting down engine\n");
						exit_requested = 1;
						break;
				default:
					break;
				}*/
			}
		}

		app->startFrame();

		/*SDL_SetRenderTarget(Graphics::renderer.get(), GUI::canvas.get());
		SDL_RenderClear(Graphics::renderer.get());
		SDL_SetRenderTarget(Graphics::renderer.get(), NULL);*/

		currentScene->Draw();
		currentGUI->Draw();

		//drawCheatSheet();
		bool show_demo_window = true;
		if (show_demo_window)
			ImGui::ShowDemoWindow(&show_demo_window);

		// put text on screen
		//if (helloworld_tex)
			//SDL_RenderCopy(Graphics::renderer.get(), helloworld_tex.get(), NULL, &helloworld_rect);

		//bkFMV->Draw();
		/*for (auto& fmv : test) {
			fmv->Draw();
		}*/
		//menuFMV->Draw();

		app->endFrame();
	}

	quit();
}