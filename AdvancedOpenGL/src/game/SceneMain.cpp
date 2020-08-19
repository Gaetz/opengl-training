#include "SceneMain.h"
#include "../engine/Assets.h"

#include <cstdlib>
#include <ctime>


SceneMain::SceneMain()
{
}

SceneMain::~SceneMain()
{
	clean();
}

void SceneMain::setGame(Game *_game)
{
	game = _game;
}

void SceneMain::load()
{
    std::srand((int) std::time(nullptr));
    //Assets::loadTexture("./assets/textures/wall.png", "wall");
    //Assets::loadShader("assets/shaders/sprite.vert", "assets/shaders/sprite.frag", "", "sprite");
}

void SceneMain::clean()
{
}

void SceneMain::pause()
{
}

void SceneMain::resume()
{
}

void SceneMain::handleEvent(const InputState &inputState)
{
}

void SceneMain::update(unsigned int dt)
{
}

void SceneMain::draw() {
}

int SceneMain::getRand(int a, int b)
{
	return std::rand() % (b - a + 1) + a;
}
