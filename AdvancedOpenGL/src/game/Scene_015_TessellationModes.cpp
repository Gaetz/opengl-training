//
// Created by gaetz on 04/12/2019.
//

#include "Scene_015_TessellationModes.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_015_TessellationModes::Scene_015_TessellationModes()
{
}

Scene_015_TessellationModes::~Scene_015_TessellationModes() {
    clean();
}

void Scene_015_TessellationModes::setGame(Game *_game) {
    game = _game;
}

void Scene_015_TessellationModes::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_015_TessellationModes::pause() {
}

void Scene_015_TessellationModes::resume() {
}

void Scene_015_TessellationModes::handleEvent(const InputState &inputState) {
}

void Scene_015_TessellationModes::load() {
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), SHADER_TECS(SHADER_NAME), SHADER_TESE(SHADER_NAME), "", SHADER_ID(SHADER_NAME));

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glPatchParameteri(GL_PATCH_VERTICES, 4);
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));
}

void Scene_015_TessellationModes::update(float dt) {

}

void Scene_015_TessellationModes::draw()
{
    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);

    shader.use();
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    glDrawArrays(GL_PATCHES, 0, 4);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
