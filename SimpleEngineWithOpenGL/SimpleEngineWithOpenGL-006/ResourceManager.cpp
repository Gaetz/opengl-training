#include "ResourceManager.h"

std::map<std::string, Texture> ResourceManager::textures;

Texture ResourceManager::loadTexture(Renderer& renderer, const string& filename, const string& name)
{
    textures[name] = loadTextureFromFile(renderer, filename.c_str());
    return textures[name];
}

Texture& ResourceManager::getTexture(const string& name) 
{
    return textures[name];
}

void ResourceManager::clear() 
{
    // (Properly) delete all textures
    textures.clear();
}

Texture ResourceManager::loadTextureFromFile(Renderer& renderer, const string& filename)
{
    Texture texture;
    texture.load(renderer, filename);
    return texture;
}