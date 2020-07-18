#pragma once
#include <string>
#include "RendererSDL.h"
using std::string;

class Texture
{
public:
	Texture();
	~Texture();

	void unload();
	bool loadSDL(RendererSDL& rendererP, const string& filenameP);
	inline SDL_Texture* toSDLTexture() const { return SDLTexture; }
	void updateInfo(int& widthOut, int& heightOut);

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

private:
	string filename;
	int width;
	int height;
	SDL_Texture* SDLTexture = nullptr;
};

