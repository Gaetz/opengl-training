//
// Created by gaetz on 04/12/2019.
//

#include "Scene_003_Triangle.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_003_Triangle::Scene_003_Triangle() {
}

Scene_003_Triangle::~Scene_003_Triangle() {
    clean();
}

void Scene_003_Triangle::setGame(Game *_game) {
    game = _game;
}

void Scene_003_Triangle::load() {
    std::srand((int) std::time(nullptr));
    Assets::loadShader("assets/shaders/003_Triangle.vert", "assets/shaders/003_Triangle.frag", "", "", "", "003_Triangle");
    shader = Assets::getShader("003_Triangle");
    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);
}

void Scene_003_Triangle::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_003_Triangle::pause() {
}

void Scene_003_Triangle::resume() {
}

void Scene_003_Triangle::handleEvent(const InputState &inputState) {
}

void Scene_003_Triangle::update(float dt) {
}

void Scene_003_Triangle::draw() {
    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);

    shader.use();
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
