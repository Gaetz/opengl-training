#pragma once
#include <SDL_rect.h>

struct Rectangle
{
	float x;
	float y;
	float width;
	float height;

	SDL_Rect toSDLRect() const
	{
		return SDL_Rect{
			static_cast<int>(x),
			static_cast<int>(y),
			static_cast<int>(width),
			static_cast<int>(height)
		};
	}
};
