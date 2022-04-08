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

    // Setup shader
    shader.compileVertexShader();
    shader.compileFragmentShader();
    shader.createShaderProgram();

    // Setup 3D scene
    view = Matrix4::createLookAt(Vector3 {0.0f, 10.0f, 1.0f}, Vector3 {0.0f, -5.0f, -6.0f}, Vector3::unitY );
    projection = Matrix4::createPerspectiveFOV(70.0f, windowWidth, windowHeight, 0.1f, 1000.0f);
    shader.use();
    shader.setMatrix4("view_matrix", view);
    shader.setMatrix4("proj_matrix", projection);

    level.load();
    levelElements = level.populateLevel();
}

InputState Game::handleInputs() {
    SDL_Event event;
    InputState inputState;
    bool inputHasChanged { false }; // Only one input for a frame
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
                isRunning = false;
                break;

            case SDL_KEYDOWN:
                if (event.key.keysym.sym == SDLK_ESCAPE) {
                    isRunning = false;
                }
                if (event.key.keysym.sym == SDLK_UP && !inputHasChanged) {
                    inputState.up = true;
                    inputHasChanged = true;
                }
                if (event.key.keysym.sym == SDLK_DOWN && !inputHasChanged) {
                    inputState.down = true;
                    inputHasChanged = true;
                }
                if (event.key.keysym.sym == SDLK_LEFT && !inputHasChanged) {
                    inputState.left = true;
                    inputHasChanged = true;
                }
                if (event.key.keysym.sym == SDLK_RIGHT && !inputHasChanged) {
                    inputState.right = true;
                    inputHasChanged = true;
                }
                break;

            default:
                break;
        }
    }
    return inputState;
}

void Game::update(float dt, const InputState& inputState) {
}

void Game::render() {
    for(auto& cube : levelElements) {
        cube.draw(shader);
    }
}

void Game::clean() {

}
