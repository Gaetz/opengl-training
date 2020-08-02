#include "Font.h"
#include "Log.h"

Font::Font()
{
}

Font::~Font()
{
}

bool Font::initialize()
{
	if (TTF_Init() != 0)
	{
		Log::error(LogCategory::System, "Failed to initialize SDL_ttf");
		return false;
	}
	return true;
}

void Font::unload()
{
	for (auto& font : fontData)
	{
		TTF_CloseFont(font.second);
	}
}

Texture* Font::renderText(const string& text, const Vector3& color, int pointSize)
{
	return nullptr;
}

void Font::addFontData(int size, TTF_Font* fontSize)
{
	fontData.emplace(size, fontSize);
}
