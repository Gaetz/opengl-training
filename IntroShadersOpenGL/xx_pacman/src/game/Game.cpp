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

    // Setup OpenGL
    glEnable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    // Setup shader
    shader.compileVertexShader();
    shader.compileFragmentShader();
    shader.createShaderProgram();

    // Setup 3D scene
    projection = Matrix4::createPerspectiveFOV(70.0f, windowWidth, windowHeight, 0.1f, 1000.0f);
    shader.use();
    shader.setMatrix4("proj_matrix", projection);
    for(int i = 0; i < 100; ++i) {
        Cube cube { Vector2 { static_cast<float>(i % 10), static_cast<float>(i / 10) }, WHITE };
        cube.load();
        cubes.push_back(cube);
    }
    level.load("assets/level.txt");

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

    for(auto& cube:cubes) {
        Vector2 offset { cube.getTilePos() };
        Matrix4 translationOffset = Matrix4::createTranslation(Vector3(offset.x, offset.y, -4.0f));
        cube.setTransform(transform * translationOffset);
    }
}

void Game::render() {
    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    glClearBufferfv(GL_COLOR, 0, bgColor);

    for(auto& cube:cubes) {
        cube.draw(shader);
    }
}

void Game::clean() {
    for(auto& cube:cubes) {
        cube.clean();
    }
}
