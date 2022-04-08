#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <SDL.h>

#include <memory>
#include <vector>

#include "Shader.h"
#include "InputState.h"
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
    InputState handleInputs();
    void update(float dt, const InputState& inputState);
    void render();
    void clean();

    bool isRunning;
    int windowWidth, windowHeight;

   private:
    float timeSinceStart;

    Matrix4 view;
    Matrix4 projection;

    Shader shader;

    vector<Cube> levelElements {};
    Level level;
};

#endif
