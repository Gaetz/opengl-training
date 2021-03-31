#include "Scene_021_ChangePrimitiveType.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_021_ChangePrimitiveType::Scene_021_ChangePrimitiveType(): totalTime(0) {

}

Scene_021_ChangePrimitiveType::~Scene_021_ChangePrimitiveType() {
    clean();
}

void Scene_021_ChangePrimitiveType::setGame(Game *_game) {
    game = _game;
}

void Scene_021_ChangePrimitiveType::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_021_ChangePrimitiveType::pause() {
}

void Scene_021_ChangePrimitiveType::resume() {
}

void Scene_021_ChangePrimitiveType::handleEvent(const InputState &inputState) {

}

void Scene_021_ChangePrimitiveType::load() {
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", SHADER_GEOM(SHADER_NAME), SHADER_ID(SHADER_NAME));

    object.load("assets/meshes/torus.sbm");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));
}

void Scene_021_ChangePrimitiveType::update(float dt) {
    totalTime += dt;
}

void Scene_021_ChangePrimitiveType::draw()
{
    static const GLfloat black[] = {0.0f, 0.0f, 0.2f, 1.0f};
    static const GLfloat one = 1.0f;
    float f = totalTime * timeScale;

    glClearBufferfv(GL_COLOR, 0, black);
    glClearBufferfv(GL_DEPTH, 0, &one);


    proj = Matrix4::createPerspectiveFOV(45.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);
    view = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -8.0f)) *
                            Matrix4::createRotationY(f * 15.0f) *
                            Matrix4::createRotationX(f * 21.0f);

    shader.use();
    shader.setMatrix4("proj_matrix", proj);
    shader.setMatrix4("mv_matrix", view);
    shader.setFloat("normal_length", sinf((float)f * 8.0f) * cosf((float)f * 6.0f) * 0.03f + 0.05f);

    object.render();
}
