#pragma once
#include "IRenderer.h"
#include "Rectangle.h"
#include <SDL.h>
#include "Window.h"
#include "Vector2.h"

class RendererSDL : public IRenderer
{
public:
	RendererSDL();
	virtual ~RendererSDL();
	RendererSDL(const RendererSDL&) = delete;
	RendererSDL& operator=(const RendererSDL&) = delete;

	bool initialize(Window& window);

	void beginDraw();
	void drawRect(const Rectangle& rect) const;
	void drawSprite(Vector2 position, float rotation, float scale, const class Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const;
	void endDraw();
	IRenderer::Type type() { return Type::SDL; }

	SDL_Renderer* toSDLRenderer() const { return SDLRenderer; }
	void close();

private:
	SDL_Renderer* SDLRenderer = nullptr;
};

