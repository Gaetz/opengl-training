#include "Window.h"
#include "Log.h"
#include "SDL_image.h"

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
	SDLWindow = SDL_CreateWindow("Parallaxes", 100, 100, width, height, 0); // 0 is flag we will use later
	if (!SDLWindow)
	{
		Log::error(SDL_LOG_CATEGORY_SYSTEM, "Failed to create window");
		return false;
	}
	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		Log::error(SDL_LOG_CATEGORY_VIDEO, "Unable to initialize SDL_image");
		return false;
	}
	return true;
}


void Window::close()
{
	SDL_DestroyWindow(SDLWindow);
}
