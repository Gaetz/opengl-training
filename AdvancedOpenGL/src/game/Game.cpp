#include "../engine/Game.h"
#include "../engine/Assets.h"
#include "../engine/Scene.h"

#include "Scene_009_Textures.h"

Game::Game() : isRunning(false),
               windowWidth(0),
               windowHeight(0) {
}

Game::~Game() {
}

void Game::init(int screenWidth, int screenHeight) {
    windowWidth = screenWidth;
    windowHeight = screenHeight;
    isRunning = true;
}

void Game::load() {
    // Game state
    changeState(std::make_unique<Scene_009_Textures>());
}

void Game::handleInputs() {
    inputManager.prepareForUpdate();
    isRunning = inputManager.pollInputs();
    const InputState &inputState = inputManager.getState();
    gameStates.back()->handleEvent(inputState);
}

void Game::update(float dt) {
    gameStates.back()->update(dt);
}

void Game::render() {
    gameStates.back()->draw();
}

void Game::clean() {
    Assets::clear();
}

void Game::changeState(unique_ptr<Scene> state) {
    // cleanup the current state
    if (!gameStates.empty()) {
        gameStates.back()->clean();
        gameStates.pop_back();
    }

    // store and load the new state
    state->setGame(this);
    gameStates.push_back(std::move(state));
    gameStates.back()->load();
}

void Game::pushState(unique_ptr<Scene> state) {
    // pause current state
    if (!gameStates.empty()) {
        gameStates.back()->pause();
    }

    // store and init the new state
    gameStates.push_back(std::move(state));
    gameStates.back()->load();
}

void Game::popState() {
    // cleanup the current state
    if (!gameStates.empty()) {
        gameStates.back()->clean();
        gameStates.pop_back();
    }

    // resume previous state
    if (!gameStates.empty()) {
        gameStates.back()->resume();
    }
}