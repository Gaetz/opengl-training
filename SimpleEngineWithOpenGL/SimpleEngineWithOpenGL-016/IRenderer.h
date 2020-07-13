#pragma once
#include "Window.h"
#include "Actor.h"

class IRenderer
{
public:
	enum class Flip
	{
		None = SDL_FLIP_NONE,
		Horizontal = SDL_FLIP_HORIZONTAL,
		Vertical = SDL_FLIP_VERTICAL
	};

	enum class Type { SDL, OGL };

	virtual ~IRenderer() {};

	virtual bool initialize(Window& window) = 0;
	virtual void beginDraw() = 0;
	virtual void drawSprite(const Actor&, const class Texture& tex, struct Rectangle srcRect, Vector2 origin, Flip flip) const	= 0;
	virtual void endDraw() = 0;
	virtual void close() = 0;
	virtual IRenderer::Type type() = 0;
};
