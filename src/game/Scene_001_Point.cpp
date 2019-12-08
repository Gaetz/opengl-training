//
// Created by gaetz on 04/12/2019.
//

#include "Scene_001_Point.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_001_Point::Scene_001_Point()
{
}

Scene_001_Point::~Scene_001_Point()
{
    clean();
}

void Scene_001_Point::setGame(Game *_game)
{
    game = _game;
}

void Scene_001_Point::load()
{
    std::srand((int) std::time(nullptr));
    //ResourceManager::loadTexture("./assets/textures/wall.png", "wall");
    //ResourceManager::loadShader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag", "", "sprite");
}

void Scene_001_Point::clean()
{
}

void Scene_001_Point::pause()
{
}

void Scene_001_Point::resume()
{
}

void Scene_001_Point::handleEvent(const InputState &inputState)
{
}

void Scene_001_Point::update(unsigned int dt)
{
}

void Scene_001_Point::draw() {
    static const GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, red);
}
