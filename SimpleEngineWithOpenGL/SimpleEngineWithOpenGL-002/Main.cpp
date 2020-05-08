#include "Game.h"

int main(int argc, char** argv)
{
	Game game;
	bool isGameInit = game.initialize();
	if (isGameInit)
	{
		game.loop();
	}
	game.close();
	return 0;
}