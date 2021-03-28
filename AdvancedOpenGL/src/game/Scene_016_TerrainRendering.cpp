//
// Created by gaetz on 04/12/2019.
//

#include "Scene_016_TerrainRendering.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_016_TerrainRendering::Scene_016_TerrainRendering():
    dmapDepth(8.0f), isFogEnabled(true), isDisplacementEnabled(true),
    wireframe(false), paused(false), totalTime(0)
{
}

Scene_016_TerrainRendering::~Scene_016_TerrainRendering() {
    clean();
}

void Scene_016_TerrainRendering::setGame(Game *_game) {
    game = _game;
}

void Scene_016_TerrainRendering::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_016_TerrainRendering::pause() {
}

void Scene_016_TerrainRendering::resume() {
}

void Scene_016_TerrainRendering::handleEvent(const InputState &inputState) {
    if(inputState.keyboardState.isDown(SDL_SCANCODE_Q)) {
        dmapDepth += 0.1f;
    }
    if(inputState.keyboardState.isDown(SDL_SCANCODE_E)) {
        dmapDepth -= 0.1f;
    }
    if(inputState.keyboardState.isJustPressed(SDL_SCANCODE_D)) {
        isDisplacementEnabled = !isDisplacementEnabled;
    }
    if(inputState.keyboardState.isJustPressed(SDL_SCANCODE_F)) {
        isFogEnabled = !isFogEnabled;
    }
    if(inputState.keyboardState.isJustPressed(SDL_SCANCODE_W)) {
        wireframe = !wireframe;
    }
    if(inputState.keyboardState.isJustPressed(SDL_SCANCODE_P)) {
        paused = !paused;
    }
}

void Scene_016_TerrainRendering::load() {
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), SHADER_TECS(SHADER_NAME), SHADER_TESE(SHADER_NAME), "", SHADER_ID(SHADER_NAME));

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glPatchParameteri(GL_PATCH_VERTICES, 4);

    glEnable(GL_CULL_FACE);

    glActiveTexture(GL_TEXTURE1);
    Assets::loadTextureKtx("assets/textures/terragen1.ktx", "terragen1");
    texDisplacement = Assets::getTextureKtx("terragen1").id;
    glBindTexture(GL_TEXTURE_2D, texDisplacement);

    glActiveTexture(GL_TEXTURE2);
    Assets::loadTextureKtx("assets/textures/terragen_color.ktx", "terragen_color");
    texColor = Assets::getTextureKtx("terragen_color").id;
    glBindTexture(GL_TEXTURE_2D, texColor);

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));
}

void Scene_016_TerrainRendering::update(float dt) {
    if (!paused)
        totalTime += dt;

    t = totalTime * 0.03f;
    r = sinf(t * 5.37f) * 15.0f + 16.0f;
    h = cosf(t * 4.79f) * 2.0f + 10.2f;
}

void Scene_016_TerrainRendering::draw()
{
    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    static const GLfloat one = 1.0f;
    glClearBufferfv(GL_COLOR, 0, bgColor);
    glClearBufferfv(GL_DEPTH, 0, &one);

    view = Matrix4::createLookAt(Vector3(sinf(t) * r, h, cosf(t) * r), Vector3::zero, Vector3(0.0f, 1.0f, 0.0f));
    proj = Matrix4::createPerspectiveFOV(45.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);

    shader.use();
    shader.setMatrix4("mv_matrix", view);
    shader.setMatrix4("proj_matrix", proj);
    shader.setMatrix4("mvp_matrix", proj * view);
    shader.setFloat("dmap_depth", isDisplacementEnabled ? dmapDepth : 0.0f);
    shader.setFloat("enable_fog", isFogEnabled ? 1.0f : 0.0f);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    glDrawArraysInstanced(GL_PATCHES, 0, 4, 64 * 64);
}
