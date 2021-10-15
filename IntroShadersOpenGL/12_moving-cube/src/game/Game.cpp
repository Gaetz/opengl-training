#include "../engine/Game.h"
#include "../engine/Texture.h"

#include <cstdlib>
#include <ctime>
#include <cmath>

Game::Game() : isRunning(false), windowWidth(0), windowHeight(0) {}

Game::~Game() {}

void Game::init(int screenWidth, int screenHeight) {
    windowWidth = screenWidth;
    windowHeight = screenHeight;
    isRunning = true;
}

void Game::load() {
    std::srand((int) std::time(nullptr));

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    projection = Matrix4::createPerspectiveFOV(70.0f, windowWidth, windowHeight, 0.1f, 1000.0f);
    static const GLfloat vertexPositions[]
    {
            -0.25f,  0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
             0.25f, -0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
             0.25f,  0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
             0.25f, -0.25f,  0.25f,
             0.25f,  0.25f, -0.25f,

             0.25f, -0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,
             0.25f,  0.25f, -0.25f,

             0.25f, -0.25f,  0.25f,
            -0.25f, -0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
             0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f, -0.25f,
            -0.25f,  0.25f, -0.25f,
            -0.25f,  0.25f,  0.25f,

            -0.25f, -0.25f,  0.25f,
             0.25f, -0.25f,  0.25f,
             0.25f, -0.25f, -0.25f,

             0.25f, -0.25f, -0.25f,
            -0.25f, -0.25f, -0.25f,
            -0.25f, -0.25f,  0.25f,

            -0.25f,  0.25f, -0.25f,
             0.25f,  0.25f, -0.25f,
             0.25f,  0.25f,  0.25f,

             0.25f,  0.25f,  0.25f,
            -0.25f,  0.25f,  0.25f,
            -0.25f,  0.25f, -0.25f
    };

    // Generate data and put it in buffer object
    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);

    // Setup vertex attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(0);

    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    shader.compileVertexShader();
    shader.compileFragmentShader();
    shader.createShaderProgram();

    shader.use();
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
    timeSinceStart += dt;
    const float t = timeSinceStart * 0.3f;
    
    Matrix4 basePosition = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -4.0f));
    Matrix4 move = Matrix4::createTranslation(Vector3(Maths::sin(2.1f * t) * 0.5f, Maths::cos(1.7f * t) * 0.5f, Maths::sin(1.3f * t) * Maths::cos(1.5f * t) * 2.0f));
    Matrix4 yRotation = Matrix4::createRotationY(t * 45.0f / 10.0f);
    Matrix4 xRotation = Matrix4::createRotationX(t * 81.0f / 10.0f);
    
    Matrix4 translation = basePosition * move;
    Matrix4 rotation = yRotation * xRotation;
    transform = translation * rotation;
}

void Game::render() {
    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);
    
    shader.use();
    shader.setMatrix4("mv_matrix", transform);
    shader.setMatrix4("proj_matrix", projection);
    
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Game::clean() {
    glDeleteVertexArrays(1, &vao);
}
