//
// Created by gaetz on 04/12/2019.
//

#include "GameState_001_Point.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


GameState_001_Point::GameState_001_Point()
{
}

GameState_001_Point::~GameState_001_Point()
{
    clean();
}

void GameState_001_Point::setGame(Game *_game)
{
    game = _game;
}

void GameState_001_Point::load()
{
    std::srand((int) std::time(nullptr));
    //ResourceManager::loadTexture("./assets/textures/wall.png", "wall");
    //ResourceManager::loadShader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag", "", "sprite");
}

void GameState_001_Point::clean()
{
}

void GameState_001_Point::pause()
{
}

void GameState_001_Point::resume()
{
}

void GameState_001_Point::handleEvent(const InputState &inputState)
{
}

void GameState_001_Point::update(unsigned int dt)
{
}

void GameState_001_Point::draw() {
    static const GLfloat red[] = {1.0f, 0.0f, 0.0f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, red);
}
