#ifndef GAMESTATE_MAIN_H
#define GAMESTATE_MAIN_H

#include "../engine/gamestate.h"

// Main scene of the game, contains all the game's logic
class GameStateMain : public GameState
{
public:
	GameStateMain();
	virtual ~GameStateMain();

	void load();
	void clean();
	void pause();
	void resume();
	void handleEvent(const InputState &);
	void update(unsigned int dt);
	void draw();
	void setGame(Game *);



private:
	Game *game;

	int getRand(int a, int b);
};

#endif
