#include "Assets.h"
#include "Log.h"
#include <sstream>

std::map<std::string, Texture> Assets::textures;

Texture Assets::loadTexture(Renderer& renderer, const string& filename, const string& name)
{
    textures[name] = loadTextureFromFile(renderer, filename.c_str());
    return textures[name];
}

Texture& Assets::getTexture(const string& name) 
{
    if (textures.find(name) == end(textures))
    {
        std::ostringstream loadError;
        loadError << "Texture " << name << " does not exist in assets manager.";
        Log::error(LogCategory::Application, loadError.str());
    }
    return textures[name];
}

void Assets::clear() 
{
    // (Properly) delete all textures
    for (auto iter : textures)
        iter.second.unload();
    textures.clear();
}

Texture Assets::loadTextureFromFile(Renderer& renderer, const string& filename)
{
    Texture texture;
    texture.load(renderer, filename);
    return texture;
}