#define SDL_MAIN_HANDLED
//disable for insecure c functions and a warning about cxx17 standard
#pragma warning( disable : 4996 )

#ifdef __SWITCH__
#include <switch.h>

//For switch only?
#define LOGURU_STACKTRACES 0

//Patch for switch not containing for loguru
#include <stdlib.h>
#include <stdarg.h>
#include <string>
int vasprintf(char** ret, const char* format, va_list args)
{
	va_list copy;
	va_copy(copy, args);

	/* Make sure it is determinate, despite manuals indicating otherwise */
	*ret = NULL;

	int count = vsnprintf(NULL, 0, format, args);
	if (count >= 0)
	{
		char* buffer = (char*)malloc(count + 1);
		if (buffer == NULL)
			count = -1;
		else if ((count = vsnprintf(buffer, count + 1, format, copy)) < 0)
			free(buffer);
		else
			*ret = buffer;
	}
	va_end(copy);  // Each va_start() or va_copy() needs a va_end()

	return count;
}

int asprintf(char** ret, const char* format, ...)
{
	va_list args;
	va_start(args, format);
	int count = vasprintf(ret, format, args);
	va_end(args);
	return(count);
}
#endif


#define LOGURU_IMPLEMENTATION 1
#define LOGURU_WITH_STREAMS 1
#define LOGURU_FILENAME_WIDTH 15
#define LOGURU_THREADNAME_WIDTH 13
#define LOGURU_STACKTRACES 0
#include <loguru.hpp>

#ifdef __APPLE__
#include <unistd.h>
#endif

#include "globals.h"
#include <Engine\Utils.h>
#include <Engine\Graphics.h>
#include <Engine\Config.h>
#include "Scene.h"
#include "Loader.h"
#include "Utils.h"

#include "Cursor.h"
#include <Engine\SapphireApp.h>

#ifndef __SWITCH__
#include <imgui.h>
#endif


int main(int argc, char** argv)
{
	Engine::Config::parse(argc, argv);
	Utils::initLog(argc, argv);

	SapphireApp_ptr app = std::make_unique<SapphireApp>();

	//Test loading screen
	//SDL_Delay(2000);

	Loader::Boot();

	// loop variables
	int exit_requested = 0;
	SDL_Event event;

#if !defined(__SWITCH__) && !defined(__APPLE__)
	//IMGUI does not like being in a dll
	ImGui::SetCurrentContext(currentGUI->imCtx);
	ImGuiIO& io = ImGui::GetIO();
#endif

#ifdef __SWITCH__
	while (!exit_requested && appletMainLoop())
#else
	while (!exit_requested)
#endif
	{
#if !defined(__SWITCH__) && !defined(__APPLE__)
		//IMGUI does not like being in a dll
		ImGui::SetCurrentContext(currentGUI->imCtx);
#endif

		if (sceneReloadFlag)
		{
			ReloadScene();
		}
		if (sceneChangeFlag)
		{
			sceneChangeFlag = false;
			_LoadScene(sceneChangeName);
		}

		while (SDL_PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
			{
				exit_requested = 1;
				break;
			}

			if (event.type == SDL_WINDOWEVENT && event.window.event == SDL_WINDOWEVENT_CLOSE && event.window.windowID == SDL_GetWindowID(Engine::Graphics::window.get()))
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

		currentScene->Draw();
		currentGUI->Draw();

		Cursor::DrawCursor();
		app->endFrame();
	}

	quit();
}