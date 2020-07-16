#pragma once
#include "IRenderer.h"
#include "Rectangle.h"
#include <SDL.h>
#include "Window.h"
#include "Vector2.h"

#include <vector>

class RendererSDL : public IRenderer
{
public:
	RendererSDL();
	virtual ~RendererSDL();
	RendererSDL(const RendererSDL&) = delete;
	RendererSDL& operator=(const RendererSDL&) = delete;

	bool initialize(Window& window);

	void beginDraw();
	void draw();
	void endDraw();
	IRenderer::Type type() { return Type::SDL; }

	void drawRect(const Rectangle& rect) const;
	void addSprite(class SpriteComponent* sprite);
	void removeSprite(class SpriteComponent* sprite);
	void drawSprite(const Actor& actor, const class Texture& tex, Rectangle srcRect, Vector2 origin, Flip flip) const;

	SDL_Renderer* toSDLRenderer() const { return SDLRenderer; }
	void close();

private:
	void drawSprites();

	std::vector<class SpriteComponent*> sprites;
	SDL_Renderer* SDLRenderer = nullptr;
};

