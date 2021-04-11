#ifndef ASSETS_H
#define ASSETS_H

#include <map>
#include <string>

#include <GL/glew.h>

#include "Texture.h"
#include "Shader.h"
#include "TextureKtx.h"
#include "ComputeShader.h"

// A static singleton Assets class that hosts several
// functions to load Textures and Shaders. Each loaded texture
// and/or shader is also stored for future reference by string
// handles. All functions and resources are static and no
// public constructor is defined.
class Assets {
public:
    // Resource storage
    static std::map<std::string, Shader> shaders;
    static std::map<std::string, Texture2D> textures;
    static std::map<std::string, TextureKtx> ktxTextures;
    static std::map<std::string, ComputeShader> computeShaders;


    // Loads (and generates) a shader program from file loading vertex, fragment (and tessellation control, evaluation,
    // geometry) shader's source code. If tcShaderFile, teShaderFile, gShaderFile are not nullptr, it also loads
    // tessellation and geometry shaders
    static Shader loadShader(const std::string &vShaderFile, const std::string &fShaderFile,
                             const std::string &tcShaderFile, const std::string &teShaderFile,
                             const std::string &gShaderFile, const std::string &name);

    // Retrieves a stored shader
    static Shader &getShader(const std::string &name);

    // Loads (and generates) a texture from file
    static Texture2D loadTexture(const std::string &file, const std::string &name);

    // Retrieves a stored texture
    static Texture2D &getTexture(const std::string &name);

    // Loads (and generates) a texture from file
    static TextureKtx loadTextureKtx(const std::string &file, const std::string &name);

    // Retrieves a stored texture
    static TextureKtx &getTextureKtx(const std::string &name);

    // Loads (and generates) a shader program from a compute shader source file
    static ComputeShader loadComputeShader(const std::string &cShaderFile, const std::string &name);

    // Retrieves a stored shader
    static ComputeShader &getComputeShader(const std::string &name);

    // Properly de-allocates all loaded resources
    static void clear();

private:
    // Private constructor, that is we do not want any actual resource manager objects.
    // Its members and functions should be publicly available (static).
    Assets() {}

    // Loads and generates a shader from file
    static Shader loadShaderFromFile(const std::string &vShaderFile, const std::string &fShaderFile,
                                     const std::string &tcShaderFile = "", const std::string &teShaderFile = "",
                                     const std::string &gShaderFile = "");

    // Loads a single texture from file
    static Texture2D loadTextureFromFile(const std::string &file);

    static ComputeShader loadComputeShaderFromFile(const std::string &cShaderFile);
};

#endif