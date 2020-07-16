#include "Assets.h"

std::map<std::string, Texture> Assets::textures;

Texture Assets::loadTexture(IRenderer& renderer, const string& filename, const string& name)
{
    textures[name] = loadTextureFromFile(renderer, filename.c_str());
    return textures[name];
}

Texture& Assets::getTexture(const string& name) 
{
    return textures[name];
}

void Assets::clear() 
{
    // (Properly) delete all textures
    textures.clear();
}

Texture Assets::loadTextureFromFile(IRenderer& renderer, const string& filename)
{
    Texture texture;
    // Not very elegant, but simpler architecture
    if (renderer.type() == IRenderer::Type::SDL)
    {
        texture.loadSDL(dynamic_cast<RendererSDL&>(renderer), filename);
    }
    return texture;
}