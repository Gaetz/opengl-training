//
// Created by gaetz on 28/08/2020.
//
#include "Scene_013_InstancedGrassBlades.h"
#include "../engine/Game.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"
#include "../engine/Log.h"
//#include PATH(SCENE_NAME, EXT)

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>

Scene_013_InstancedGrassBlades::Scene_013_InstancedGrassBlades() {}

Scene_013_InstancedGrassBlades::~Scene_013_InstancedGrassBlades() {
    clean();
}

void Scene_013_InstancedGrassBlades::setGame(Game *_game) {
    game = _game;
}

void Scene_013_InstancedGrassBlades::load() {
    std::srand((int) std::time(nullptr));
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", "", SHADER_ID(SHADER_NAME));
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    static const GLfloat grassBlade[] =
    {
        -0.3f, 0.0f,
        0.3f, 0.0f,
        -0.20f, 1.0f,
        0.1f, 1.3f,
        -0.05f, 2.3f,
        0.0f, 3.3f
    };

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(grassBlade), grassBlade, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    glActiveTexture(GL_TEXTURE1);
    Assets::loadTextureKtx("assets/textures/grass_length.ktx", "grass_length");
    texGrassLength = Assets::getTextureKtx("grass_length").id;
    glBindTexture(GL_TEXTURE_2D, texGrassLength);

    glActiveTexture(GL_TEXTURE2);
    Assets::loadTextureKtx("assets/textures/grass_orientation.ktx", "grass_orientation");
    texGrassOrientation = Assets::getTextureKtx("grass_orientation").id;
    glBindTexture(GL_TEXTURE_2D, texGrassOrientation);

    glActiveTexture(GL_TEXTURE3);
    Assets::loadTextureKtx("assets/textures/grass_color.ktx", "grass_color");
    texGrassColor = Assets::getTextureKtx("grass_color").id;
    glBindTexture(GL_TEXTURE_2D, texGrassColor);

    glActiveTexture(GL_TEXTURE4);
    Assets::loadTextureKtx("assets/textures/grass_bend.ktx", "grass_bend");
    texGrassBend = Assets::getTextureKtx("grass_bend").id;
    glBindTexture(GL_TEXTURE_2D, texGrassBend);

    projection = Matrix4::createPerspectiveFOV(70.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);
    shader = Assets::getShader(SHADER_ID(SHADER_NAME));
    shader.use();
}

void Scene_013_InstancedGrassBlades::clean() {

}

void Scene_013_InstancedGrassBlades::pause() {
}

void Scene_013_InstancedGrassBlades::resume() {
}

void Scene_013_InstancedGrassBlades::handleEvent(const InputState &inputState) {
    
}

void Scene_013_InstancedGrassBlades::update(float dt) {
    float t = Timer::getTimeSinceStart() * 0.20f + 1.0f;
    float r = 20.0f;
    // view = Matrix4::createLookAt(Vector3(Maths::sin(t) * r, 25.0f, Maths::cos(t) * r), 
    //                                 Vector3(0.0f, -50.0f, 0.0f), 
    //                                 Vector3::unitY);
    view = Matrix4::createLookAt(Vector3(Maths::sin(t) * r, 25.0f, Maths::cos(t) * r), 
                                    Vector3(0.0f, 15.0f, 10.0f), 
                                    Vector3::unitY)
            * Matrix4::createRotationX(Maths::pi)
            * Matrix4::createTranslation(Vector3(0, 30, 0));
}

void Scene_013_InstancedGrassBlades::draw() 
{
    shader.setMatrix4("mvp_matrix", projection * view);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glBindVertexArray(vao);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 6, 1024 * 1024);
}

