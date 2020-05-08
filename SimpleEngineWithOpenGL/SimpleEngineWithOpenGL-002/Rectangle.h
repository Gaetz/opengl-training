#pragma once
#include <SDL_rect.h>

struct Rectangle
{
	int x;
	int y;
	int width;
	int height;

	SDL_Rect toSDLRect() 
	{
		return SDL_Rect{ x, y, width, height };
	}
};
