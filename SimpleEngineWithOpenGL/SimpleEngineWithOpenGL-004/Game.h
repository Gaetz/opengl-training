#pragma once
#include "Window.h"
#include "Renderer.h"
#include "Vector2.h"
class Game
{
public:
	Game();
	bool initialize();
	void loop();
	void close();

private:
	void processInput();
	void update(float dt);
	void render();

	bool isRunning;
	Window window;
	Renderer renderer;

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;

	Rectangle topWall;
	Rectangle bottomWall;
	Rectangle rightWall;
	const float wallThickness = 10;

	Vector2 ballPos;
	Vector2 ballVelocity;
	const float ballSize = 10;

	Vector2 paddlePos;
	Vector2 paddleVelocity;
	const float paddleWidth = 10;
	const float paddleHeight = 96;
	float paddleDirection;

};

