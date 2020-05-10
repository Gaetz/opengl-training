#include "Game.h"

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	return isWindowInit; // Return bool && bool && bool ...to detect error
}

void Game::loop()
{
	while (isRunning)
	{
		processInput();
		update();
		render();
	}
}

void Game::close()
{
	window.close();
	SDL_Quit();
}

void Game::processInput()
{
}

void Game::update()
{
}

void Game::render()
{
}
