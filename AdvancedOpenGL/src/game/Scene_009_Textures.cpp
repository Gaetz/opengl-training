//
// Created by gaetz on 28/08/2020.
//

#include "Scene_009_Textures.h"
#include "../engine/Timer.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_009_Textures::Scene_009_Textures()
{
}

Scene_009_Textures::~Scene_009_Textures() {
    clean();
}

void Scene_009_Textures::setGame(Game *_game) {
    game = _game;
}

void Scene_009_Textures::load() {
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

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    shader = Assets::getShader("007_spinning_cube");
}

void Scene_009_Textures::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_009_Textures::pause() {
}

void Scene_009_Textures::resume() {
}

void Scene_009_Textures::handleEvent(const InputState &inputState) {
}

void Scene_009_Textures::update(float dt) {

    for(int i = 0; i < 24; ++i)
    {
        const float t = i + Timer::getTimeSinceStart() * 0.3f;
        transform[i] = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -10.0f))
            * Matrix4::createRotationY(t * 45.0f / 10.0f)
            * Matrix4::createRotationX(t * 21.0f / 10.0f)
            * Matrix4::createTranslation(Vector3(Maths::sin(2.1f * t) * 2.0f, Maths::cos(1.7f * t) * 2.0f, Maths::sin(1.3f * t) * Maths::cos(1.5f * t) * 2.0f));
    }
}

void Scene_009_Textures::draw() 
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
