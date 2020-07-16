#include "Window.h"
#include "Log.h"

Window::Window() : SDLWindow(nullptr), width(WINDOW_WIDTH), height(WINDOW_HEIGHT)
{
}

bool Window::initialize()
{
	int sdlInitResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlInitResult != 0) {
		Log::error(SDL_LOG_CATEGORY_VIDEO, "Unable to initialize SDL");
		return false;
	}

	SDLWindow = SDL_CreateWindow("3D Basics", 100, 100, width, height, SDL_WINDOW_OPENGL);
	if (!SDLWindow)
	{
		Log::error(SDL_LOG_CATEGORY_SYSTEM, "Failed to create window");
		return false;
	}
	return true;
}

void Window::close()
{
	SDL_DestroyWindow(SDLWindow);
}
