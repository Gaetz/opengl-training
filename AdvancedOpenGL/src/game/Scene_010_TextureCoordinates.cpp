//
// Created by gaetz on 28/08/2020.
//
#include "Scene_010_TextureCoordinates.h"
#include "../engine/Game.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"
#include "../engine/Log.h"
//#include PATH(SCENE_NAME, EXT)

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>

Scene_010_TextureCoordinates::Scene_010_TextureCoordinates() : texIndex(0)
{
}

Scene_010_TextureCoordinates::~Scene_010_TextureCoordinates() {
    clean();
}

void Scene_010_TextureCoordinates::setGame(Game *_game) {
    game = _game;
}

void Scene_010_TextureCoordinates::load() {
    std::srand((int) std::time(nullptr));
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", "", SHADER_ID(SHADER_NAME));
    Assets::loadTextureKtx("assets/textures/pattern1.ktx", "pattern1");
    #define B 0x00, 0x00, 0x00, 0x00
    #define W 0xFF, 0xFF, 0xFF, 0xFF
    static const GLubyte texData[] =
    {
        B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
        W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
        B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
        W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
        B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
        W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
        B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
        W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
        B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
        W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
        B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
        W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
        B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
        W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
        B, W, B, W, B, W, B, W, B, W, B, W, B, W, B, W,
        W, B, W, B, W, B, W, B, W, B, W, B, W, B, W, B,
    };
    #undef B
    #undef W

    glGenTextures(1, &texObject[0]);
    glBindTexture(GL_TEXTURE_2D, texObject[0]);
    glTexStorage2D(GL_TEXTURE_2D, 1, GL_RGB8, 16, 16);
    glTexSubImage2D(GL_TEXTURE_2D, 0, 0, 0, 16, 16, GL_RGBA, GL_UNSIGNED_BYTE, texData);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

    texObject[1] = Assets::getTextureKtx("pattern1").id;

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));
    projection = Matrix4::createPerspectiveFOV(70.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);
    object.load("assets/meshes/torus_nrms_tc.sbm");
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    shader.use();
    shader.setMatrix4("proj_matrix", projection);
}

void Scene_010_TextureCoordinates::clean() {

}

void Scene_010_TextureCoordinates::pause() {
}

void Scene_010_TextureCoordinates::resume() {
}

void Scene_010_TextureCoordinates::handleEvent(const InputState &inputState) {
    if(inputState.keyboardState.isJustPressed(SDL_SCANCODE_T)) {
        texIndex = ++texIndex % 2;
    }
}

void Scene_010_TextureCoordinates::update(float dt) {
    float t = Timer::getTimeSinceStart();
    Quaternion rotY { Vector3::unitY, t * Maths::toRadians(19.3f) };
    Quaternion rotZ { Vector3::unitZ, t * Maths::toRadians(21.1f) };
    Quaternion rotation = Quaternion::concatenate(rotY, rotZ);
    transform = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -3.0f)) * rotation.asMatrix();
}

void Scene_010_TextureCoordinates::draw() 
{
    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    static const GLfloat ones[] = { 1.0f };
    glClearBufferfv(GL_COLOR, 0, bgColor);
    glClearBufferfv(GL_DEPTH, 0, ones);
    glBindTexture(GL_TEXTURE_2D, texObject[texIndex]);

    shader.setMatrix4("mv_matrix", transform);

    object.render();
}

