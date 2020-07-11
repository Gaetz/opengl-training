#include "ResourceManager.h"

std::map<std::string, Texture> ResourceManager::textures;

Texture ResourceManager::loadTexture(IRenderer& renderer, const string& filename, const string& name)
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

Texture ResourceManager::loadTextureFromFile(IRenderer& renderer, const string& filename)
{
    Texture texture;
    // Not very elegant, but simpler architecture
    if (renderer.type() == IRenderer::Type::SDL)
    {
        texture.loadSDL(dynamic_cast<RendererSDL&>(renderer), filename);
    }
    return texture;
}