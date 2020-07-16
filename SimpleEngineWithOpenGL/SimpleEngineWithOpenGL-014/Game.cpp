#include "Game.h"
#include "Actor.h"
#include "SpriteComponent.h"
#include "AnimSpriteComponent.h"
#include "Timer.h"
#include "ResourceManager.h"
#include "BackgroundSpriteComponent.h"

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);
	return isWindowInit && isRendererInit; // Return bool && bool && bool ...to detect error
}

void Game::load()
{
	// Load textures
	ResourceManager::loadTexture(renderer, "Res\\Airplane.png", "Airplane");
	ResourceManager::loadTexture(renderer, "Res\\Base.png", "Base");
	ResourceManager::loadTexture(renderer, "Res\\Missile.png", "Missile");
	ResourceManager::loadTexture(renderer, "Res\\Projectile.png", "Projectile");
	ResourceManager::loadTexture(renderer, "Res\\TileBrown.png", "TileBrown");
	ResourceManager::loadTexture(renderer, "Res\\TileBrownSelected.png", "TileBrownSelected");
	ResourceManager::loadTexture(renderer, "Res\\TileGreen.png", "TileGreen");
	ResourceManager::loadTexture(renderer, "Res\\TileGreenSelected.png", "TileGreenSelected");
	ResourceManager::loadTexture(renderer, "Res\\TileGrey.png", "TileGrey");
	ResourceManager::loadTexture(renderer, "Res\\TileGreySelected.png", "TileGreySelected");
	ResourceManager::loadTexture(renderer, "Res\\TileTan.png", "TileTan");
	ResourceManager::loadTexture(renderer, "Res\\TileTanSelected.png", "TileTanSelected");
	ResourceManager::loadTexture(renderer, "Res\\Tower.png", "Tower");

	ResourceManager::loadTexture(renderer, "Res\\TileRedSelected.png", "TileRedSelected");
	ResourceManager::loadTexture(renderer, "Res\\TileRed.png", "TileRed");

	grid = new Grid();
}

void Game::processInput()
{
	// SDL Event
	SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
		case SDL_QUIT:
			isRunning = false;
			break;
		}
	}
	// Keyboard state
	const Uint8* keyboardState = SDL_GetKeyboardState(nullptr);
	// Escape: quit game
	if (keyboardState[SDL_SCANCODE_ESCAPE])
	{
		isRunning = false;
	}
	// Actor input
	isUpdatingActors = true;
	for (auto actor : actors)
	{
		actor->processInput(keyboardState);
	}
	isUpdatingActors = false;

	// Process mouse
	int x, y;
	Uint32 buttons = SDL_GetMouseState(&x, &y);
	if (SDL_BUTTON(buttons) & SDL_BUTTON_LEFT)
	{
		grid->processClick(x, y);
	}
}

void Game::update(float dt)
{
	// Update actors 
	isUpdatingActors = true;
	for(auto actor: actors) 
	{
		actor->update(dt);
	}
	isUpdatingActors = false;

	// Move pending actors to actors
	for (auto pendingActor: pendingActors)
	{
		actors.emplace_back(pendingActor);
	}
	pendingActors.clear();

	// Delete dead actors
	vector<Actor*> deadActors;
	for (auto actor : actors)
	{
		if (actor->getState() == Actor::ActorState::Dead)
		{
			deadActors.emplace_back(actor);
		}
	}
	for (auto deadActor : deadActors)
	{
		delete deadActor;
	}
}

void Game::render()
{
	renderer.beginDraw();
	renderer.draw();
	renderer.endDraw();
}

void Game::loop()
{
	Timer timer;
	float dt = 0;
	while (isRunning)
	{
		float dt = timer.computeDeltaTime() / 1000.0f;
		processInput();
		update(dt);
		render();
		timer.delayTime();
	}
}

void Game::unload()
{
	// Delete actors
	// Because ~Actor calls RemoveActor, have to use a different style loop
	while (!actors.empty())
	{
		delete actors.back();
	}

	// Resources
	ResourceManager::clear();
}

void Game::close()
{
	renderer.close();
	window.close();
	SDL_Quit();
}

void Game::addActor(Actor* actor)
{
	if (isUpdatingActors)
	{
		pendingActors.emplace_back(actor);
	}
	else
	{
		actors.emplace_back(actor);
	}
}

void Game::removeActor(Actor* actor)
{
	// Erase actor from the two vectors
	auto iter = std::find(begin(pendingActors), end(pendingActors), actor);
	if (iter != end(pendingActors))
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, end(pendingActors) - 1);
		pendingActors.pop_back();
	}
	iter = std::find(begin(actors), end(actors), actor);
	if (iter != end(actors))
	{
		std::iter_swap(iter, end(actors) - 1);
		actors.pop_back();
	}
}
