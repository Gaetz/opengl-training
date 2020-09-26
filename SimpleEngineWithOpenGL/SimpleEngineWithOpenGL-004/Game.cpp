#include "Game.h"
#include "Timer.h"

bool Game::initialize()
{
	bool isWindowInit = window.initialize();
	bool isRendererInit = renderer.initialize(window);

	int windowWidth = window.getWidth();
	int windowHeight = window.getHeight();
	topWall = { 0, 0, static_cast<float>(windowWidth), wallThickness };
	bottomWall = { 0, windowHeight - wallThickness, static_cast<float>(windowWidth), wallThickness };
	rightWall = { windowWidth - wallThickness, 0, wallThickness, static_cast<float>(windowHeight) };

	return isWindowInit && isRendererInit; // Return bool && bool && bool ...to detect error
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
	// Paddle move
	if (keyboardState[SDL_SCANCODE_W])
	{
		paddleDirection = -1;
	}
	if (keyboardState[SDL_SCANCODE_S])
	{
		paddleDirection = 1;
	}
}

void Game::update(float dt)
{
	// Paddle move
	paddlePos += paddleVelocity * dt * paddleDirection;
	if (paddlePos.y < paddleHeight / 2 + wallThickness)
	{
		paddlePos.y = paddleHeight / 2 + wallThickness;
	}
	if (paddlePos.y > window.getHeight() - paddleHeight / 2 - wallThickness)
	{
		paddlePos.y = window.getHeight() - paddleHeight / 2 - wallThickness;
	}

	// Ball move
	ballPos += ballVelocity * dt;
	if (ballPos.y < ballSize / 2 + wallThickness) {
		ballPos.y = ballSize / 2 + wallThickness;
		ballVelocity.y *= -1;
	}
	else if (ballPos.y > window.getHeight() - ballSize / 2 - wallThickness) {
		ballPos.y = window.getHeight() - ballSize / 2 - wallThickness;
		ballVelocity.y *= -1;
	}
	if (ballPos.x > window.getWidth() - ballSize / 2 - wallThickness) {
		ballPos.x = window.getWidth() - ballSize / 2 - wallThickness;
		ballVelocity.x *= -1;
	}

	// Ball-Paddle collision
	Vector2 diff = ballPos - paddlePos;
	if (fabsf(diff.y) <= paddleHeight / 2
		&& fabsf(diff.x) <= paddleWidth / 2 + ballSize / 2
		&& ballVelocity.x < 0)
	{
		ballVelocity.x *= -1;
		ballPos.x = paddlePos.x + paddleWidth / 2 + ballSize / 2;
	}

	// Restart automatically
	if (ballPos.x < 0) {
		ballVelocity.x *= -1;
		ballPos.x = window.getWidth() / 2.f;
	}
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

void Game::close()
{
	renderer.close();
	window.close();
	SDL_Quit();
}