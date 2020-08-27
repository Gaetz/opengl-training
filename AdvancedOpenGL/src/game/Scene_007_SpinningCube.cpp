//
// Created by gaetz on 04/12/2019.
//

#include "Scene_007_SpinningCube.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_007_SpinningCube::Scene_007_SpinningCube() {
}

Scene_007_SpinningCube::~Scene_007_SpinningCube() {
    clean();
}

void Scene_007_SpinningCube::setGame(Game *_game) {
    game = _game;
}

void Scene_007_SpinningCube::load() {
    std::srand((int) std::time(nullptr));
    Assets::loadShader("assets/shaders/007_spinning_cube.vert", "assets/shaders/007_spinning_cube.frag", "", "", "", "007_spinning_cube");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    projection = Matrix4::createPerspectiveFOV(70.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);
    static const GLfloat vertexPositions[] =
    {
            -0.25f,  0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
             0.25f, -0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
             0.25f,  0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
             0.25f, -0.25f,  0.25f,
             0.25f,  0.25f, -0.25f,

             0.25f, -0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,
             0.25f,  0.25f, -0.25f,

             0.25f, -0.25f,  0.25f,
            -0.25f, -0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,
            -0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
             0.25f, -0.25f,  0.25f,
             0.25f, -0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
            -0.25f, -0.25f,  0.25f,

            -0.25f,  0.25f, -0.25f,
             0.25f,  0.25f, -0.25f,
             0.25f,  0.25f,  0.25f,

             0.25f,  0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
            -0.25f,  0.25f, -0.25f
    };

    // Generate data and put it in buffer object
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    // Setup vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    shader = Assets::getShader("007_spinning_cube");
}

void Scene_007_SpinningCube::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_007_SpinningCube::pause() {
}

void Scene_007_SpinningCube::resume() {
}

void Scene_007_SpinningCube::handleEvent(const InputState &inputState) {
}

void Scene_007_SpinningCube::update(unsigned int dt) {
    timeSinceStart = (float)SDL_GetTicks() / 1000.0f;
    const float t = timeSinceStart / 1000.0f;
    transform = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -4.0f)) * Matrix4::createRotationX(t * 200.0f) * Matrix4::createRotationZ(t * 200.0f);
        /* * Matrix4::createTranslation(Vector3(Maths::sin(2.1f * t) * 0.5f, Maths::cos(1.7f * t) * 0.5f, Maths::sin(1.3f * t) * Maths::cos(1.5f * t) * 2.0f))
        * * Matrix4::createRotationY(t * 45.0f)
        * Matrix4::createRotationX(t * 81.0f);
        */
}

void Scene_007_SpinningCube::draw() {

    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);
    
    shader.use();
    shader.setMatrix4("mv_matrix", transform);
    shader.setMatrix4("proj_matrix", projection);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
}
