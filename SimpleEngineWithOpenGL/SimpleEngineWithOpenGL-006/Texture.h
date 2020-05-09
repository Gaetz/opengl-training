#pragma once
#include <string>
#include "Renderer.h"
using std::string;

class Texture
{
public:
	Texture();
	~Texture();

	bool load(Renderer& rendererP, const string& filenameP);
	inline SDL_Texture* toSDLTexture() const { return SDLTexture; }

private:
	string filename;
	SDL_Texture* SDLTexture = nullptr;
};

