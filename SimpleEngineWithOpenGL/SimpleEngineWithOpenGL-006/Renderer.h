#pragma once
#include "Rectangle.h"
#include <SDL.h>
#include "Window.h"

class Renderer
{
public:
	Renderer();
	bool initialize(Window& window);

	void beginDraw();
	void drawRect(Rectangle& rect);
	void endDraw();

	inline SDL_Renderer* toSDLRenderer() const { return SDLRenderer; }
	void close();

private:
	SDL_Renderer* SDLRenderer;

	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;
};

