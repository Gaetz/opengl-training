#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <SDL.h>

#include <memory>
#include <vector>

#include "Shader.h"
#include "../game/Cube.h"
#include "../game/Level.h"

using std::vector;

// This game class runs a simple game loop
class Game {
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
    GLuint vao;
    GLuint buffer;
    float timeSinceStart;

    Matrix4 transform;
    Matrix4 projection;

    vector<Cube> cubes;
    Level level;

    Shader shader;
};

#endif
