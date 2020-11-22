#ifndef GAME_H
#define GAME_H


#include <SDL.h>
#include <GL/glew.h>
#include <vector>
#include <memory>

using std::vector;

// This game class runs a simple game loop
class Game
{
public:
	Game();
	virtual ~Game();

	void init(int screenWidth, int screenHeight);
	void load();
	void handleInputs();
	void update(float dt);
	void render();
	void clean();

	bool isRunning;
	int windowWidth, windowHeight;

private:
	GLuint shaderProgram;
	GLuint vao;
};

#endif
