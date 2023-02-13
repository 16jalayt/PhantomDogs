#pragma once

#include <SDL2/SDL.h>
#include "sprite.h"
#include "SDL_ptr.h"
#include <globals.h>
#include <functional>

class Button : public Sprite
{
public:
	Button(int x, int y, int w, int h, const char* file = NULL, RenderParent parent = RenderParent::canvas, bool enabled = true);
	Button(SDL_Rect rect, const char* file = NULL, RenderParent parent = RenderParent::canvas, bool enabled = true);
	Button(Scaled_Rect rect, const char* file = NULL, RenderParent parent = RenderParent::canvas, bool enabled = true);
	virtual ~Button();
	void Draw();
	void Event(SDL_Event event);
	void setDebug(bool debug);
	//void (*callback)();
	std::function<void()> callback;

private:
	//TODO: make enabled in click handler
	bool _enabled;
	bool _debugView;
	//SDL_Rect _pos = { 0, 0, 0, 0 };
	//Sprite _graphic;
};

using Button_ptr = std::shared_ptr<Button>;