#pragma once
#include <memory>
#include <Engine/Sprite.h>
#include <SDL2/SDL_events.h>

class Sprite : public Engine::Sprite
{
public:
	void HoverCheck(SDL_Event event);
private:
};

using Sprite_ptr = std::shared_ptr<Sprite>;