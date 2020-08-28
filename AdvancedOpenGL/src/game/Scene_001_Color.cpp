//
// Created by gaetz on 04/12/2019.
//

#include "Scene_001_Color.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_001_Color::Scene_001_Color()
{
}

Scene_001_Color::~Scene_001_Color()
{
    clean();
}

void Scene_001_Color::setGame(Game *_game)
{
    game = _game;
}

void Scene_001_Color::load()
{
    std::srand((int) std::time(nullptr));
    //Assets::loadTexture("./assets/textures/wall.png", "wall");
    //Assets::loadShader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag", "", "sprite");
}

void Scene_001_Color::clean()
{
}

void Scene_001_Color::pause()
{
}

void Scene_001_Color::resume()
{
}

void Scene_001_Color::handleEvent(const InputState &inputState)
{
}

void Scene_001_Color::update(float dt)
{
}

void Scene_001_Color::draw() {
    static const GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, red);
}
