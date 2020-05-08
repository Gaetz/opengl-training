#pragma once
#include "Window.h"
class Game
{
public:
	Game();
	bool initialize();
	void loop();
	void close();

private:
	void processInput();
	void update();
	void render();

	Window window;
	bool isRunning;
};

