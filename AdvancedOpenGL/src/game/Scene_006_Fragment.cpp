//
// Created by gaetz on 04/12/2019.
//

#include "Scene_006_Fragment.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_006_Fragment::Scene_006_Fragment() {
}

Scene_006_Fragment::~Scene_006_Fragment() {
    clean();
}

void Scene_006_Fragment::setGame(Game *_game) {
    game = _game;
}

void Scene_006_Fragment::load() {
    std::srand((int) std::time(nullptr));
    //Assets::loadShader("assets/shaders/006_tessellation.vert", "assets/shaders/006_fragment.frag", "", "", "", "006_fragment");
    Assets::loadShader("assets/shaders/006_fragment_b.vert", "assets/shaders/006_fragment_b.frag", "", "", "", "006_fragment_b");

    glCreateVertexArrays(1, &vao);
    glBindVertexArray(vao);

    shader = Assets::getShader("006_fragment_b");
}

void Scene_006_Fragment::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_006_Fragment::pause() {
}

void Scene_006_Fragment::resume() {
}

void Scene_006_Fragment::handleEvent(const InputState &inputState) {
}

void Scene_006_Fragment::update(unsigned int dt) {
    timeSinceStart = (float)SDL_GetTicks() / 1000.0f;
}

void Scene_006_Fragment::draw() {

    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);
    
    GLfloat offset[] = { (float)sin(timeSinceStart) *0.5f + 0.5f, (float)cos(timeSinceStart) *0.5f + 0.5f, 0.0f, 1.0f};
    glVertexAttrib4fv(0, offset);
    shader.use();
    
    glDrawArrays(GL_TRIANGLES, 0, 3);
}
