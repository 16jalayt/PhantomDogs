#pragma once

#include <SDL2/SDL.h>

#include "sprite.h"
#include "SDL_ptr.h"
#include "globals.h"

class Button : public Sprite
{
public:
	Button(int x, int y, int w, int h, const char* file = NULL, RenderParent parent = RenderParent::canvas, bool enabled = true);
	Button(SDL_Rect rect, const char* file = NULL, RenderParent parent = RenderParent::canvas, bool enabled = true);
	Button(Scaled_Rect rect, const char* file = NULL, RenderParent parent = RenderParent::canvas, bool enabled = true);
	void Draw();
	void setDebug(bool debug);

private:
	//TODO: make enabled in click handler
	bool _enabled;
	bool _debugView = false;
	//SDL_Rect _pos = { 0, 0, 0, 0 };
	//Sprite _graphic;
};

using Button_ptr = std::shared_ptr<Button>;