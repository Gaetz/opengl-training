#include "Game.h"
int main(int argc, char** argv)
{
	Game game;
	bool isGameInit = game.initialize();
	if (isGameInit)
	{
		game.load();
		game.loop();
		game.unload();
	}
	game.close();
	return 0;
}