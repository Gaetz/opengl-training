#include "Scene_023_ComputeShaderGrid.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"
#include "../engine/Log.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>

Scene_023_ComputeShaderGrid::Scene_023_ComputeShaderGrid() {

}

Scene_023_ComputeShaderGrid::~Scene_023_ComputeShaderGrid() {
    clean();
}

void Scene_023_ComputeShaderGrid::setGame(Game *_game) {
    game = _game;
}

void Scene_023_ComputeShaderGrid::clean() {
    delete quadTexture;
    delete quadVertex;
    delete quadIndex;
}

void Scene_023_ComputeShaderGrid::pause() {
}

void Scene_023_ComputeShaderGrid::resume() {
}

void Scene_023_ComputeShaderGrid::handleEvent(const InputState &inputState) {

}

void Scene_023_ComputeShaderGrid::load() {

    // Create quads
    Rgba * quadTexture = new Rgba[1280 * 720];
    Coords * quadVertex = new Coords[4];
    unsigned short int * quadIndex = new unsigned short int[3];

    quadVertex[0].x = -1.0f;
    quadVertex[0].y = 1.0f;

    quadVertex[1].x = -1.0f;
    quadVertex[1].y = -1.0f;

    quadVertex[2].x = 1.0f;
    quadVertex[2].y = 1.0f;

    quadVertex[3].x = 1.0f;
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

    for (int x = 0; x < 1280; x++) {
        for (int y = 0; y < 720; y++) {
            quadTexture[x + y * 1280].Red = 1.0f;
            quadTexture[x + y * 1280].Green = .5f;
            quadTexture[x + y * 1280].Blue = .0f;
            quadTexture[x + y * 1280].Alpha = 1.0f;
        }
    }

    // Setup texture
    glGenTextures(1, &quadTextureID);
    glBindTexture(GL_TEXTURE_2D, quadTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glGenerateMipmap(GL_TEXTURE_2D);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA32F, 1280, 720, 0, GL_RGBA, GL_FLOAT, NULL);
    glBindTexture(GL_TEXTURE_2D, 0);

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

    // Run Compute shader
    computeShader.use();
    glBindTexture(GL_TEXTURE_2D, quadTextureID);
    glBindImageTexture(0, quadTextureID, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
    glDispatchCompute(80, 45, 1);
    glMemoryBarrier(GL_SHADER_IMAGE_ACCESS_BARRIER_BIT);

    // Unbind
    glBindImageTexture(0, 0, 0, GL_FALSE, 0, GL_WRITE_ONLY, GL_RGBA32F);
    glBindTexture(GL_TEXTURE_2D, 0);
    glUseProgram(0);
}

void Scene_023_ComputeShaderGrid::update(float dt) {

}

void Scene_023_ComputeShaderGrid::draw()
{
    glEnable(GL_CULL_FACE);
    renderShader.use();
    glBindVertexArray(quadVAO);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, quadTextureID);
    glDrawElements(GL_TRIANGLE_STRIP, 4, GL_UNSIGNED_SHORT, (GLvoid *)0);

    // If you want to unbind everything
    glBindTexture(GL_TEXTURE_2D, 0);
    glActiveTexture(0);
    glBindVertexArray(0);
    glUseProgram(0);
}