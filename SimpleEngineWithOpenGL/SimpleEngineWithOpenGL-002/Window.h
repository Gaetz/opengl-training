#pragma once
#include <SDL.h>
class Window
{
public:
	Window();
	bool initialize();
	void close();

	SDL_Window* getSDLWindow();

private:
	SDL_Window* SDLWindow;

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
};

