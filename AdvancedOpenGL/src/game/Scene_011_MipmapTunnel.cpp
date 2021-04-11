//
// Created by gaetz on 28/08/2020.
//
#include "Scene_011_MipmapTunnel.h"
#include "../engine/Game.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"
#include "../engine/Log.h"
//#include PATH(SCENE_NAME, EXT)

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>

Scene_011_MipmapTunnel::Scene_011_MipmapTunnel() {}

Scene_011_MipmapTunnel::~Scene_011_MipmapTunnel() {
    clean();
}

void Scene_011_MipmapTunnel::setGame(Game *_game) {
    game = _game;
}

void Scene_011_MipmapTunnel::load() {
    std::srand((int) std::time(nullptr));
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", "", SHADER_ID(SHADER_NAME));
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    Assets::loadTextureKtx("assets/textures/brick.ktx", "brick");
    Assets::loadTextureKtx("assets/textures/ceiling.ktx", "ceiling");
    Assets::loadTextureKtx("assets/textures/floor.ktx", "floor");
    texWall = Assets::getTextureKtx("brick").id;
    texCeiling = Assets::getTextureKtx("ceiling").id;
    texFloor = Assets::getTextureKtx("floor").id;
    projection = Matrix4::createPerspectiveFOV(70.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);
    shader = Assets::getShader(SHADER_ID(SHADER_NAME));

    int i;
    GLuint textures[] = { texFloor, texWall, texCeiling };
    for (i = 0; i < 3; i++)
    {
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    }
    shader.use();
}

void Scene_011_MipmapTunnel::clean() {

}

void Scene_011_MipmapTunnel::pause() {
}

void Scene_011_MipmapTunnel::resume() {
}

void Scene_011_MipmapTunnel::handleEvent(const InputState &inputState) {

}

void Scene_011_MipmapTunnel::update(float dt) {
    float t = Timer::getTimeSinceStart();
    int i;
    GLuint textures[] = { texWall, texFloor, texWall, texCeiling };
    for (i = 0; i < 4; i++)
    {
        transform[i] = Matrix4::createRotationZ(Maths::piOver2 * static_cast<float>(i))
            * Matrix4::createTranslation(Vector3(-0.5f, 0.0f, -10.0f))
            * Matrix4::createRotationY(Maths::piOver2)
            * Matrix4::createScale(Vector3(30.0f, 1.0f, 1.0f));
    }
}

void Scene_011_MipmapTunnel::draw()
{
    float t = Timer::getTimeSinceStart();
    shader.setFloat("offset", t * 0.003f);
    int i;
    GLuint textures[] = { texWall, texFloor, texWall, texCeiling };
    for (i = 0; i < 4; i++)
    {
        Matrix4 view = Matrix4::identity;
        Matrix4 mvp = projection * view * transform[i];
        shader.setMatrix4("mvp_matrix", mvp);
        glBindTexture(GL_TEXTURE_2D, textures[i]);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
}

