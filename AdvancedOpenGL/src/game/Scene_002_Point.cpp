//
// Created by gaetz on 04/12/2019.
//

#include "Scene_002_Point.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_002_Point::Scene_002_Point() {
}

Scene_002_Point::~Scene_002_Point() {
    clean();
}

void Scene_002_Point::setGame(Game *_game) {
    game = _game;
}

void Scene_002_Point::load() {
    std::srand((int) std::time(nullptr));
    Assets::loadShader("assets/shaders/002_Point.vert", "assets/shaders/002_Point.frag", "", "", "", "002_Point");
    shader = Assets::getShader("002_Point");
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glPointSize(40.0f);
}

void Scene_002_Point::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_002_Point::pause() {
}

void Scene_002_Point::resume() {
}

void Scene_002_Point::handleEvent(const InputState &inputState) {
}

void Scene_002_Point::update(float dt) {
}

void Scene_002_Point::draw() {

    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);

    shader.use();
    glDrawArrays(GL_POINTS, 0, 1);
}
