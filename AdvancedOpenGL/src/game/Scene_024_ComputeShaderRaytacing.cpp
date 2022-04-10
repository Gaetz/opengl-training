#include "Scene_024_ComputeShaderRaytracing.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"
#include "../engine/Log.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>

Scene_024_ComputeShaderRaytracing::Scene_024_ComputeShaderRaytracing() {

}

Scene_024_ComputeShaderRaytracing::~Scene_024_ComputeShaderRaytracing() {
    clean();
}

void Scene_024_ComputeShaderRaytracing::setGame(Game *_game) {
    game = _game;
}

void Scene_024_ComputeShaderRaytracing::clean() {

}

void Scene_024_ComputeShaderRaytracing::pause() {
}

void Scene_024_ComputeShaderRaytracing::resume() {
}

void Scene_024_ComputeShaderRaytracing::handleEvent(const InputState &inputState) {

}

void Scene_024_ComputeShaderRaytracing::load() {
    // Create quads
    Rgba * quadTexture = new Rgba[512 * 512];
    Coords * quadVertex = new Coords[4];
    unsigned short int * quadIndex = new unsigned short int[3];

    quadVertex[0].x = -512.0f/1280.0f * 1.5f;
    quadVertex[0].y = 1.0f;

    quadVertex[1].x = -512.0f/1280.0f * 1.5f;
    quadVertex[1].y = -1.0f;

    quadVertex[2].x = 512.0f/1280.0f * 1.5f;
    quadVertex[2].y = 1.0f;

    quadVertex[3].x = 512.0f/1280.0f * 1.5f;
    quadVertex[3].y = -1.0f;

    quadIndex[0] = 0;
    quadIndex[1] = 1;
    quadIndex[2] = 2;
    quadIndex[3] = 3;

    quadVertex[0].s = 0.0f;
    quadVertex[0].t = 0.0f;
    quadVertex[1].s = 0.0f;
    quadVertex[1].t = 1.0f;
    quadVertex[2].s = 1.0f;
    quadVertex[2].t = 0.0f;
    quadVertex[3].s = 1.0f;
    quadVertex[3].t = 1.0f;

    for (int x = 0; x < 512; x++) {
        for (int y = 0; y < 512; y++) {
            quadTexture[x + y * 512].Red = 1.0f;
            quadTexture[x + y * 512].Green = .5f;
            quadTexture[x + y * 512].Blue = .0f;
            quadTexture[x + y * 512].Alpha = 1.0f;
        }
    }

    // Setup texture
    glGenTextures(1, &quadTextureID);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, quadTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, texWidth, texHeight, 0, GL_RGBA, GL_FLOAT, NULL);
    glBindImageTexture(0, quadTextureID, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);

    // OpenGL setup
    glGenBuffers(1, &quadIBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, 4 * sizeof(unsigned short int), quadIndex, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    glGenBuffers(1, &quadVBO);
    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(Coords) * 4, 0, GL_STATIC_DRAW);
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(Coords) * 4, quadVertex);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glGenVertexArrays(1, &quadVAO);
    glBindVertexArray(quadVAO);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIBO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), 0);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(GLfloat), (GLvoid *)(sizeof(GLfloat) * 2));
    glEnableVertexAttribArray(1);

    glBindVertexArray(0);


    // Load shaders
    Assets::loadComputeShader(SHADER_COMP(SHADER_NAME), SHADER_ID(SHADER_NAME));
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", "", SHADER_ID(SHADER_NAME));

    computeShader = Assets::getComputeShader(SHADER_ID(SHADER_NAME));
    renderShader = Assets::getShader(SHADER_ID(SHADER_NAME));
}

void Scene_024_ComputeShaderRaytracing::update(float dt) {

}

void Scene_024_ComputeShaderRaytracing::draw()
{
    // Launch compute shaders!
    computeShader.use();
    glDispatchCompute((GLuint)texWidth, (GLuint)texHeight, 1);
  
    // Make sure writing to image has finished before read
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);
  
    // normal drawing pass
    renderShader.use();
    glBindVertexArray(quadVAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, quadTextureID);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}