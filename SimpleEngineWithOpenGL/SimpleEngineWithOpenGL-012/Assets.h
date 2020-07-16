#pragma once
#include <map>
#include <string>
#include "Texture.h"
using std::map;
using std::string;

// A static singleton Assets class that hosts several
// functions to load resources. Each loaded resource is also 
// stored for future reference by string handles. All functions 
// and resources are static and no public constructor is defined.
class Assets
{
public:
    static std::map<std::string, Texture> textures;

    // Loads a texture from file
    static Texture loadTexture(Renderer& renderer, const string& filename, const string& name);

    // Retrieves a stored texture
    static Texture& getTexture(const std::string& name);

    // Properly de-allocates all loaded resources
    static void clear();

private:
    Assets() {}

    // Loads a single texture from file
    static Texture loadTextureFromFile(Renderer& renderer, const string& filename);
};

