#pragma once
#include "Rectangle.h"
#include <SDL.h>
#include "Window.h"

class Renderer
{
public:
	Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	bool initialize(Window& window);
	void beginDraw();
	void drawRect(Rectangle& rect);
	void endDraw();
	void close();

private:
	SDL_Renderer* SDLRenderer = nullptr;

};

