#pragma once
#include "Window.h"
#include "Renderer.h"
class Game
{
public:
	static Game& instance()
	{
		static Game inst;
		return inst;
	}

	Game(const Game&) = delete;
	Game& operator=(const Game&) = delete;
	Game(Game&&) = delete;
	Game& operator=(Game&&) = delete;

private:
	Game() : isRunning(true) {}

public:
	bool initialize();
	void loop();
	void close();

private:
	void processInput();
	void update();
	void render();

	bool isRunning;
	Window window;
	Renderer renderer;
};

