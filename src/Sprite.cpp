#include "Sprite.h"
#include "Cursor.h"

void Sprite::HoverCheck(SDL_Event event)
{
	if (MouseCollision(event))
		Cursor::setCursor(hoverCursor);
	//else
		//Cursor::resetCursor();
}