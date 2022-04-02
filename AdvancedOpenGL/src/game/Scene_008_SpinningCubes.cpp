//
// Created by gaetz on 04/12/2019.
//

#include "Scene_008_SpinningCubes.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_008_SpinningCubes::Scene_008_SpinningCubes()
{
}

Scene_008_SpinningCubes::~Scene_008_SpinningCubes() {
    clean();
}

void Scene_008_SpinningCubes::setGame(Game *_game) {
    game = _game;
}

void Scene_008_SpinningCubes::load() {
    std::srand((int) std::time(nullptr));
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", "", SHADER_ID(SHADER_NAME));

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

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));
}

void Scene_008_SpinningCubes::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_008_SpinningCubes::pause() {
}

void Scene_008_SpinningCubes::resume() {
}

void Scene_008_SpinningCubes::handleEvent(const InputState &inputState) {
}

void Scene_008_SpinningCubes::update(float dt) {
    for(int i = 0; i < 24; ++i)
    {
        const float t = i + Timer::getTimeSinceStart() * 0.3f;
        transform[i] = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -10.0f))
            * Matrix4::createRotationY(t * Maths::toRadians(45.0f))
            * Matrix4::createRotationX(t * Maths::toRadians(21.0f))
            * Matrix4::createTranslation(Vector3(Maths::sin(2.1f * t) * 2.0f, Maths::cos(1.7f * t) * 2.0f, Maths::sin(1.3f * t) * Maths::cos(1.5f * t) * 2.0f));
    }
}

void Scene_008_SpinningCubes::draw()
{
    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);

    shader.use();
    shader.setMatrix4("proj_matrix", projection);
    for(int i = 0; i < 24; ++i)
    {
        shader.setMatrix4("mv_matrix", transform[i]);
        glDrawArrays(GL_TRIANGLES, 0, 36);
    }
}
