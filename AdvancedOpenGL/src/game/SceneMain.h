#ifndef GAMESTATE_MAIN_H
#define GAMESTATE_MAIN_H

#include "../engine/Scene.h"

// Main scene of the game, contains all the game's logic
class SceneMain : public Scene
{
public:
	SceneMain();
	virtual ~SceneMain();

	void load();
	void clean();
	void pause();
	void resume();
	void handleEvent(const InputState &);
	void update(float dt);
	void draw();
	void setGame(Game *);



private:
	Game *game;

	int getRand(int a, int b);
};

#endif
