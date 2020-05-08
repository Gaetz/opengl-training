#pragma once
#include <SDL.h>
class Window
{
public:
	Window();
	bool initialize();
	void close();

private:
	SDL_Window* SDLWindow;

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
};

