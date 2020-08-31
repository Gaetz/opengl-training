//
// Created by gaetz on 28/08/2020.
//
#include "Scene_009_TextureAsData.h"
#include "../engine/Game.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"
//#include PATH(SCENE_NAME, EXT)

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>

Scene_009_TextureAsData::Scene_009_TextureAsData()
{
}

Scene_009_TextureAsData::~Scene_009_TextureAsData() {
    clean();
}

void Scene_009_TextureAsData::setGame(Game *_game) {
    game = _game;
}

void Scene_009_TextureAsData::load() {
    std::srand((int) std::time(nullptr));
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", "", SHADER_ID(SHADER_NAME));

    // Generate a name for the texture
    glGenTextures(1, &texture);

    // Now bind it to the context using the GL_TEXTURE_2D binding point
    glBindTexture(GL_TEXTURE_2D, texture);

    // Specify the amount of storage we want to use for the texture
    glTexStorage2D(GL_TEXTURE_2D,   // 2D texture
                    8,               // 8 mipmap levels
                    GL_RGBA32F,      // 32-bit floating-point RGBA data
                    256, 256);       // 256 x 256 texels

    // Define some data to upload into the texture
    float * data = new float[256 * 256 * 4];

    // generate_texture() is a function that fills memory with image data
    generateTexture(data, 256, 256);

    // Assume the texture is already bound to the GL_TEXTURE_2D target
    glTexSubImage2D(GL_TEXTURE_2D,  // 2D texture
                    0,              // Level 0
                    0, 0,           // Offset 0, 0
                    256, 256,       // 256 x 256 texels, replace entire image
                    GL_RGBA,        // Four channel data
                    GL_FLOAT,       // Floating point data
                    data);          // Pointer to data

    // Free the memory we allocated before - \GL now has our data
    delete [] data;

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));
}

void Scene_009_TextureAsData::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_009_TextureAsData::pause() {
}

void Scene_009_TextureAsData::resume() {
}

void Scene_009_TextureAsData::handleEvent(const InputState &inputState) {
}

void Scene_009_TextureAsData::update(float dt) {

}

void Scene_009_TextureAsData::draw() 
{
    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);
    
    shader.use();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Scene_009_TextureAsData::generateTexture(float * data, int width, int height)
{

    int x, y;
    for (y = 0; y < height; y++)
    {
        for (x = 0; x < width; x++)
        {
            data[(y * width + x) * 4 + 0] = (float)((x & y) & 0xFF) / 255.0f;
            data[(y * width + x) * 4 + 1] = (float)((x | y) & 0xFF) / 255.0f;
            data[(y * width + x) * 4 + 2] = (float)((x ^ y) & 0xFF) / 255.0f;
            data[(y * width + x) * 4 + 3] = 1.0f;
        }
    }
}