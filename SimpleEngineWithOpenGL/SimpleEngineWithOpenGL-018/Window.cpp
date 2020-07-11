#include "Window.h"
#include "Log.h"
#include "SDL_image.h"
#include <GL/glew.h>

Window::Window() : SDLWindow(nullptr), width(WINDOW_WIDTH), height(WINDOW_HEIGHT), context(nullptr)
{
}

bool Window::initialize()
{
	int sdlInitResult = SDL_Init(SDL_INIT_VIDEO);
	if (sdlInitResult != 0) {
		Log::error(SDL_LOG_CATEGORY_VIDEO, "Unable to initialize SDL");
		return false;
	}

	// Set OpenGL attributes
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 3);
	// Request a color buffer with 8-bits per RGBA channel
	SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
	SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
	// Enable double buffering
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	// Force OpenGL to use hardware acceleration
	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);

	SDLWindow = SDL_CreateWindow("Parallaxes", 100, 100, width, height, SDL_WINDOW_OPENGL);
	if (!SDLWindow)
	{
		Log::error(SDL_LOG_CATEGORY_SYSTEM, "Failed to create window");
		return false;
	}

	context = SDL_GL_CreateContext(SDLWindow);
	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		Log::error(SDL_LOG_CATEGORY_VIDEO, "Failed to initialize GLEW.");
		return false;
	}

	// On some platforms, GLEW will emit a benign error code, so clear it
	glGetError();

	if (IMG_Init(IMG_INIT_PNG) == 0)
	{
		Log::error(SDL_LOG_CATEGORY_VIDEO, "Unable to initialize SDL_image");
		return false;
	}
	return true;
}

void Window::close()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(SDLWindow);
}
