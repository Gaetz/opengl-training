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

    object.load("assets/meshes/dragon.sbm");
    glDisable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));
}

void Scene_019_ModifyGeometry::update(float dt) {
    totalTime += dt;
}

void Scene_019_ModifyGeometry::draw()
{
        static const GLfloat black[] = { 0.0f, 0.0f, 0.0f, 1.0f };
        static const GLfloat one = 1.0f;
        float f = totalTime * timeScale;

        glClearBufferfv(GL_COLOR, 0, black);
        glClearBufferfv(GL_DEPTH, 0, &one);

        shader.use();

        proj = Matrix4::createPerspectiveFOV(45.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);
        view = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -20.0f)) *
                                Matrix4::createRotationY(f * 5.0f) *
                                Matrix4::createRotationX(f * 100.0f);

        shader.setMatrix4("mvpMatrix", proj * view);
        shader.setMatrix4("mvMatrix", view);

        Vector3 vViewpoint { sinf(f * 2.1f) * 70.0f, cosf(f * 1.4f) * 70.0f, sinf(f * 0.7f) * 70.0f };
        shader.setVector3f("viewpoint", vViewpoint);
        Vector3 lightPosition { -10.0f, 40.0f, 200.0f };
        shader.setVector3f("vLightPosition", lightPosition);

        object.render();
}
