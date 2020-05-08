#include "Window.h"
#include "Log.h"

Window::Window() : SDLWindow(nullptr)
{
}

bool Window::initialize()
{
	int sdlInitResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlInitResult != 0) {
		Log::error("Unable to initialize SDL");
		return false;
	}
	SDLWindow = SDL_CreateWindow("Wall Pong", 100, 100, 1024, 768, 0); // 0 is flag we will use later
	if (!SDLWindow)
	{
		Log::error("Failed to create window");
		return false;
	}
	return true;
}

void Window::close()
{
	SDL_DestroyWindow(SDLWindow);
}

SDL_Window* Window::getSDLWindow()
{
	return SDLWindow;
}
