#pragma once
#include <string>
#include "RendererOGL.h"
using std::string;

class Texture
{
public:
	Texture();
	~Texture();

	void unload();
	//bool loadSDL(RendererSDL& rendererP, const string& filenameP);
	bool loadOGL(RendererOGL& rendererP, const string& filenameP);

	unsigned int getTextureID() const { return textureID; }

	inline SDL_Texture* toSDLTexture() const { return SDLTexture; }
	void updateInfo(int& widthOut, int& heightOut);
	void setActive(int index = 0) const;
	void createFromSurface(struct SDL_Surface* surface);
	void createForRendering(int widthP, int heightP, unsigned int format);

	inline int getWidth() const { return width; }
	inline int getHeight() const { return height; }

private:
	unsigned int textureID;
	string filename;
	int width;
	int height;
	SDL_Texture* SDLTexture = nullptr;
};

