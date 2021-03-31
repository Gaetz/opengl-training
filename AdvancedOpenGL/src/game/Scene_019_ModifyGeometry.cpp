#include "Scene_019_ModifyGeometry.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_019_ModifyGeometry::Scene_019_ModifyGeometry(): totalTime(0) {

}

Scene_019_ModifyGeometry::~Scene_019_ModifyGeometry() {
    clean();
}

void Scene_019_ModifyGeometry::setGame(Game *_game) {
    game = _game;
}

void Scene_019_ModifyGeometry::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_019_ModifyGeometry::pause() {
}

void Scene_019_ModifyGeometry::resume() {
}

void Scene_019_ModifyGeometry::handleEvent(const InputState &inputState) {

}

void Scene_019_ModifyGeometry::load() {
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", SHADER_GEOM(SHADER_NAME), SHADER_ID(SHADER_NAME));

    object.load("assets/meshes/torus.sbm");

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));
}

void Scene_019_ModifyGeometry::update(float dt) {
    totalTime += dt;
}

void Scene_019_ModifyGeometry::draw()
{
    static const GLfloat black[] = {0.0f, 0.0f, 0.2f, 1.0f};
    static const GLfloat one = 1.0f;
    float f = totalTime * timeScale;

    glClearBufferfv(GL_COLOR, 0, black);
    glClearBufferfv(GL_DEPTH, 0, &one);

    shader.use();

    proj = Matrix4::createPerspectiveFOV(45.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);
    view = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -3.0f)) *
                            Matrix4::createRotationY(45.0f) *
                            Matrix4::createRotationX(81.0f);

    shader.setMatrix4("proj_matrix", proj);
    shader.setMatrix4("mv_matrix", view);
    shader.setFloat("explode_factor", sinf((float)f * 8.0f) * cosf((float)f * 6.0f) * 0.7f + 0.1f);

    object.render();
}
