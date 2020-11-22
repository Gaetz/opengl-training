#include "../engine/Game.h"
#include <cmath>

Game::Game() : isRunning(false), windowWidth(0), windowHeight(0) {}

Game::~Game() {}

void Game::init(int screenWidth, int screenHeight) {
    windowWidth = screenWidth;
    windowHeight = screenHeight;
    isRunning = true;
}

void Game::load() {
    GLfloat points[] = {0.0f, 0.5f, 0.0f, 0.5f, -0.5f, 0.0f, -0.5f, -0.5f, 0.0f};
    GLfloat colors[] = {
        1.0f, 0.0f,  0.0f,
        0.0f, 1.0f,  0.0f,
        0.0f, 0.0f,  1.0f
    };

    GLuint pointsVbo = 0;
    glGenBuffers (1, &pointsVbo);
    glBindBuffer (GL_ARRAY_BUFFER, pointsVbo);
    glBufferData (GL_ARRAY_BUFFER, sizeof (points), points, GL_STATIC_DRAW); 
 
    GLuint colorsVbo = 0;
    glGenBuffers (1, &colorsVbo);
    glBindBuffer (GL_ARRAY_BUFFER, colorsVbo);
    glBufferData (GL_ARRAY_BUFFER, sizeof (colors), colors, GL_STATIC_DRAW); 

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glBindBuffer(GL_ARRAY_BUFFER, colorsVbo);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    shader.compileVertexShader();
    shader.compileFragmentShader();
    shader.createShaderProgram();

/*
    shader.use();
    int matrixLocation = glGetUniformLocation(shader.programId, "matrix");
    glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrix);
*/
}

void Game::handleInputs() {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                }
                break;

            default:
                break;
        }
    }
}

void Game::update(float dt) {
    if (fabs(lastPosition) > 1.0f) { 
        speed = -speed; 
    } 

    matrix[12] = speed * dt + lastPosition; 
    lastPosition = matrix[12]; 

    shader.use();
    int matrixLocation = glGetUniformLocation(shader.programId, "matrix");
    glUniformMatrix4fv(matrixLocation, 1, GL_FALSE, matrix);
}

void Game::render() {
    shader.use();
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}

void Game::clean() {}
