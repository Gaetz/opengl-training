#include "Texture.h"
#include "Log.h"
#include <SDL_image.h>

Texture::Texture(): filename(""), width(0), height(0), SDLTexture(nullptr)
{
}

Texture::~Texture()
{
}

void Texture::unload()
{
	if (SDLTexture)
	{
		SDL_DestroyTexture(SDLTexture);
	}
}

bool Texture::load(Renderer& renderer, const string& filenameP)
{
	filename = filenameP;
	// Load from file
	SDL_Surface* surf = IMG_Load(filename.c_str());
	if (!surf)
	{
		Log::error(LogCategory::Application, "Failed to load texture file " + filename);
		return false;
	}
	width = surf->w;
	height = surf->h;

	// Create texture from surface
	SDLTexture = SDL_CreateTextureFromSurface(renderer.toSDLRenderer(), surf);
	SDL_FreeSurface(surf);
	if (!SDLTexture)
	{
		Log::error(LogCategory::Render, "Failed to convert surface to texture for "+ filename);
		return false;
	}
	Log::info("Loaded texture " + filename);
	return true;
}

void Texture::updateInfo(int& widthOut, int& heightOut)
{
	widthOut = width;
	heightOut = height;
}
