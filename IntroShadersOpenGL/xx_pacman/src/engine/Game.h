#ifndef GAME_H
#define GAME_H

#include <GL/glew.h>
#include <SDL.h>

#include <memory>
#include <array>

#include "Shader.h"

using std::array;

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
    Shader shader;
};

#endif
