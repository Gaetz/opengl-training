#pragma once
#include "Rectangle.h"
#include <SDL.h>
#include "Window.h"
#include "Vector2.h"

class Renderer
{
public:
	enum class Flip
	{
		None = SDL_FLIP_NONE,
		Horizontal = SDL_FLIP_HORIZONTAL,
		Vertical = SDL_FLIP_VERTICAL
	};

	Renderer();
	~Renderer();
	Renderer(const Renderer&) = delete;
	Renderer& operator=(const Renderer&) = delete;

	bool initialize(Window& window);

	void beginDraw();
	void drawRect(const Rectangle& rect) const;
	void drawSprite(Vector2 position, float rotation, float scale, const class Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const;
	void endDraw();

	SDL_Renderer* toSDLRenderer() const { return SDLRenderer; }
	void close();

private:
	SDL_Renderer* SDLRenderer = nullptr;
};

