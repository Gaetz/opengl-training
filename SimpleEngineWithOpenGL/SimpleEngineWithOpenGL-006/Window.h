#pragma once
#include <SDL.h>

const int WINDOW_WIDTH = 1024;
const int WINDOW_HEIGHT = 768;

class Window
{
public:
	Window();
	bool initialize();
	void close();

	SDL_Window* getSDLWindow();
	int getWidth();
	int getHeight();

private:
	SDL_Window* SDLWindow;
	int width;
	int height;

	Window(const Window&) = delete;
	Window& operator=(const Window&) = delete;
};

