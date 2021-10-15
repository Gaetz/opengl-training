#include "../engine/Game.h"
#include "../engine/Texture.h"

#include <cmath>

Game::Game() : isRunning(false), windowWidth(0), windowHeight(0) {}

Game::~Game() {}

void Game::init(int screenWidth, int screenHeight) {
    windowWidth = screenWidth;
    windowHeight = screenHeight;
    isRunning = true;
}

void Game::load() {
    GLfloat points[] {
        -0.5f, -0.5f,  0.0f,
         0.5f, -0.5f,  0.0f,
         0.5f,  0.5f,  0.0f,
 
         0.5f,  0.5f,  0.0f,
        -0.5f,  0.5f,  0.0f,
        -0.5f, -0.5f,  0.0f
    };
 
    GLfloat texcoords[] { 
        0.0f, 1.0f,
        0.0f, 0.0f,
        1.0f, 0.0f,

        1.0f, 0.0f,
        1.0f, 1.0f,
        0.0f, 1.0f
    };

    GLuint pointsVbo = 0;
    glGenBuffers(1, &pointsVbo);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(points), points, GL_STATIC_DRAW);

    GLuint texVbo;
    glGenBuffers(1, &texVbo);
    glBindBuffer(GL_ARRAY_BUFFER, texVbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(texcoords), texcoords, GL_STATIC_DRAW);

    GLuint vao = 0;
    glGenVertexArrays(1, &vao);
    
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, pointsVbo);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

    glBindBuffer(GL_ARRAY_BUFFER, texVbo);
    int dimensions = 2;  // 2d data for texture coords
    glVertexAttribPointer(1, dimensions, GL_FLOAT, GL_FALSE, 0, NULL);

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    Texture texture;
    texture.load("assets/character.png");
    texture.use();

    shader.compileVertexShader();
    shader.compileFragmentShader();
    shader.createShaderProgram();

    shader.use();
    //int texLoc = glGetUniformLocation(shader.programId, "basicTexture");
    //glUniform1i (texLoc, 0); // use active texture 0

    int vec2Loc = glGetUniformLocation(shader.programId, "iResolution");
    glUniform2f (vec2Loc, 1280, 720); 
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

}

void Game::render() {
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

void Game::clean() {}
