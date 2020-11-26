#include "Scene_012_ArrayTextureAlienRain.h"
#include "../engine/Game.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"
#include "../engine/Log.h"
//#include PATH(SCENE_NAME, EXT)

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>

Scene_012_ArrayTextureAlienRain::Scene_012_ArrayTextureAlienRain() {}

Scene_012_ArrayTextureAlienRain::~Scene_012_ArrayTextureAlienRain() {
    clean();
}

void Scene_012_ArrayTextureAlienRain::setGame(Game *_game) {
    game = _game;
}

void Scene_012_ArrayTextureAlienRain::load() {
    std::srand((int) std::time(nullptr));
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", "", SHADER_ID(SHADER_NAME));
    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    Assets::loadTextureKtx("assets/textures/aliens.ktx", "aliens");
    texAliens = Assets::getTextureKtx("aliens").id;
    glBindTexture(GL_TEXTURE_2D_ARRAY, texAliens);
    glTexParameteri(GL_TEXTURE_2D_ARRAY, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);

    glGenBuffers(1, &rainBuffer);
    glBindBuffer(GL_UNIFORM_BUFFER, rainBuffer);
    glBufferData(GL_UNIFORM_BUFFER, 256 * sizeof(Vector4), NULL, GL_DYNAMIC_DRAW);

    for (int i = 0; i < 256; i++)
    {
        dropletXOffset[i] = randomFloat() * 2.0f - 1.0f;
        dropletRotSpeed[i] = (randomFloat() + 0.5f) * ((i & 1) ? -3.0f : 3.0f);
        dropletFallSpeed[i] = randomFloat() + 0.2f;
    }
    //projection = Matrix4::createPerspectiveFOV(70.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);
    shader = Assets::getShader(SHADER_ID(SHADER_NAME));

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    shader.use();
}

void Scene_012_ArrayTextureAlienRain::clean() {

}

void Scene_012_ArrayTextureAlienRain::pause() {
}

void Scene_012_ArrayTextureAlienRain::resume() {
}

void Scene_012_ArrayTextureAlienRain::handleEvent(const InputState &inputState) {
    
}

void Scene_012_ArrayTextureAlienRain::update(float dt) {

}

void Scene_012_ArrayTextureAlienRain::draw() 
{
    float t = Timer::getTimeSinceStart();
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, rainBuffer);
    Vector4 * droplet = (Vector4 *)glMapBufferRange(GL_UNIFORM_BUFFER, 0, 256 * sizeof(Vector4), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);

    for (int i = 0; i < 256; i++)
    {
        droplet[i][0] = dropletXOffset[i];
        droplet[i][1] = 2.0f - fmodf((t + float(i)) * dropletFallSpeed[i], 4.31f);
        droplet[i][2] = t * dropletRotSpeed[i];
        droplet[i][3] = 0.0f;
    }
    glUnmapBuffer(GL_UNIFORM_BUFFER);

    int alienIndex;
    for (alienIndex = 0; alienIndex < 256; alienIndex++)
    {
        glVertexAttribI1i(0, alienIndex);
        glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    }
}

