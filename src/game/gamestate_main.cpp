#include "gamestate_main.h"
#include "../engine/resource_manager.h"

#include <cstdlib>
#include <ctime>


GameStateMain::GameStateMain()
{
}

GameStateMain::~GameStateMain()
{
	clean();
}

void GameStateMain::setGame(Game *_game)
{
	game = _game;
}

void GameStateMain::load()
{
    std::srand((int) std::time(nullptr));
    //ResourceManager::loadTexture("./assets/textures/wall.png", "wall");
    //ResourceManager::loadShader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag", "", "sprite");
}

void GameStateMain::clean()
{
}

void GameStateMain::pause()
{
}

void GameStateMain::resume()
{
}

void GameStateMain::handleEvent(const InputState &inputState)
{
}

void GameStateMain::update(unsigned int dt)
{
}

void GameStateMain::draw() {
}

int GameStateMain::getRand(int a, int b)
{
	return std::rand() % (b - a + 1) + a;
}
