//
// Created by gaetz on 04/12/2019.
//

#include "Scene_004_PassingData.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_004_PassingData::Scene_004_PassingData() {
}

Scene_004_PassingData::~Scene_004_PassingData() {
    clean();
}

void Scene_004_PassingData::setGame(Game *_game) {
    game = _game;
}

void Scene_004_PassingData::load() {
    std::srand((int) std::time(nullptr));
    Assets::loadShader("assets/shaders/004_PassingData.vert", "assets/shaders/004_PassingData.frag", "", "", "", "004_PassingData");
    shader = Assets::getShader("004_PassingData");
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void Scene_004_PassingData::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_004_PassingData::pause() {
}

void Scene_004_PassingData::resume() {
}

void Scene_004_PassingData::handleEvent(const InputState &inputState) {
}

void Scene_004_PassingData::update(float dt) {
    timeSinceStart = (float)SDL_GetTicks() / 1000.0f;
    displayColor = Color((float)sin(timeSinceStart) *0.5f * 255.0f, (float)cos(timeSinceStart) *0.5f * 255.0f, 0.0f, 255);
}

void Scene_004_PassingData::draw() {

    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);

    GLfloat offset[] = { (float)sin(timeSinceStart) *0.5f + 0.5f, (float)cos(timeSinceStart) *0.5f + 0.5f, 0.0f, 1.0f};
    glVertexAttrib4fv(0, offset);
    glVertexAttrib4fv(1, displayColor.toGlArray());

    shader.use();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
