//TODO:strip everything except drawCheatSheet()
//TODO: update convention for engine includes
#include "GUI.h"
#include <string>

#if !defined(__SWITCH__) && !defined(__APPLE__)
#include <imgui.h>
#include <imgui_impl_sdl2.h>
#include <imgui_impl_sdlrenderer2.h>
#include <imgui_stdlib.h>
#include <imgui_internal.h>
#endif
#include "Globals.h"
#include <Engine/Config.h>
#include "Loader.h"
#include <Engine/GUI.h>
#include "Cursor.h"

GUI::GUI() :Engine::GUI()
{
	Cursor::Init();
}

void GUI::Draw()
{
	Engine::GUI::Draw();
	drawCheatSheet();
}

//Stub out as not using yet
#if defined(__SWITCH__) || defined(__APPLE__)
void GUI::drawCheatSheet()
{
}
#endif

#if !defined(__SWITCH__) && !defined(__APPLE__)
void GUI::drawCheatSheet()
{
	//TODO: key combo to toggle
	if (Engine::Config::debugMenuOpen)
	{
		//Forces to be immoveable
		//ImGui::SetNextWindowPos(ImVec2(0, 0));
		ImGui::SetNextWindowSize(ImVec2(700, 500));

		//Todo: temp
		//ImGui::SetNextWindowCollapsed(true);

		// Pass a pointer to our bool variable (the window will have a closing button that will clear the bool when clicked)
		ImGui::Begin("Cheet Sheet", &cheatSheetOpen,
			ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoSavedSettings);
		//ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoSavedSettings);

		//ImGui::SameLine();
		//ImGui::Separator();
		//HelpMarker("Using TableNextRow() + calling TableSetColumnIndex() _before_ each cell, in a loop.");
		if (ImGui::BeginTabBar("MyTabBar"))
		{
			if (ImGui::BeginTabItem("General"))
			{
				std::string inputScene = currentScene->sceneName;
				//TODO:redo flags
				if (ImGui::InputText("Scene Num", &inputScene, ImGuiInputTextFlags_EnterReturnsTrue))
				{
					//printf("changed!\n");
					//std::string sceneName = std::to_string(sceneNum);
					//sceneChangeName = inputScene;
					//sceneNum already set
					//sceneNum = changeTo;
					//sceneChangeFlag = true;
					Loader::loadScene(inputScene);
				}
				//ToggleButtonV2("hi", &toggle);
				if (ImGui::Button("Reload scene"))
					ReloadScene();
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Inventory"))
			{
				//ImGui::Checkbox("test", &check);
				if (ImGui::Button("Click Me"))
					printf("Ow! Stop it!\n");
				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Events"))
			{
				if (ImGui::BeginTable("table1", 4))
				{
					for (int i = 0; i < 550; i++)
					{
						ImGui::TableNextColumn();
						ImGui::Checkbox((std::to_string(i + 1000) + ":" + flagDesc[i]).c_str(), &flags[i]);
						if (ImGui::IsItemHovered(ImGuiHoveredFlags_DelayNormal)) // With a delay
							ImGui::SetTooltip(flagDesc[i].c_str());
					}
					ImGui::EndTable();
				}

				ImGui::EndTabItem();
			}
			if (ImGui::BeginTabItem("Editor"))
			{
				//Begin editing button
				// toggle for button debug
				//allow drag of sprites
				//show xy/props of selected sprite
				ToggleButtonV2("isEditing", &isEditing);
				ImGui::SameLine();
				ImGui::Text("Edit mode");

				ToggleButtonV2("debugHot", &Engine::Config::debugHot);
				ImGui::SameLine();
				ImGui::Text("Show debug hotzones");

				ImGui::EndTabItem();
			}
			//TODO: new tab with map like Humongous
			ImGui::EndTabBar();
		}

		ImGui::End();
	}
}
#endif