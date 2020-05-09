#include "Game.h"

Game::Game():
	isRunning(true),
	ballPos({ 100, 100 }), 
	ballVelocity({ 100, 100 }),
	paddlePos({ 50, 100 }),
	paddleVelocity({ 0, 80 }),
	wallThickness(10),
	topWall(Rectangle()),
	bottomWall(Rectangle()),
	rightWall(Rectangle())
{
}

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);

	topWall = { 0, 0, static_cast<float>(window.getWidth()), wallThickness };
	bottomWall = { 0, window.getHeight() - wallThickness, static_cast<float>(window.getWidth()), wallThickness };
	rightWall = { window.getWidth() - wallThickness, 0, wallThickness, static_cast<float>(window.getHeight()) };

	return isWindowInit && isRendererInit; // Return bool && bool && bool ...to detect error
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
	renderer.close();
	window.close();
	SDL_Quit();
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
}

void Game::update()
{
}

void Game::render()
{
	renderer.beginDraw();

	renderer.drawRect(topWall);
	renderer.drawRect(bottomWall);
	renderer.drawRect(rightWall);

	Rectangle ballRect = { ballPos.x - ballSize / 2, ballPos.y - ballSize / 2, ballSize, ballSize };
	renderer.drawRect(ballRect);

	Rectangle paddleRect = { paddlePos.x - paddleWidth / 2, paddlePos.y - paddleHeight / 2, paddleWidth, paddleHeight };
	renderer.drawRect(paddleRect);

	renderer.endDraw();
}
