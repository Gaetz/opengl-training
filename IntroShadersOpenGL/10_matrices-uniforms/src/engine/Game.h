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
    Shader shader;
    GLuint vao;

    float speed = 1.0f;
    float lastPosition = 0.5f;
    float matrix[16] {
        1.0f, 0.0f, 0.0f, 0.0f, // first column
        0.0f, 1.0f, 0.0f, 0.0f, // second column
        0.0f, 0.0f, 1.0f, 0.0f, // third column
        0.5f, 0.0f, 0.0f, 1.0f // fourth column
    };
};

#endif
