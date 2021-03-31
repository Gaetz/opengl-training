#include "Scene_020_GenerateGeometry.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_020_GenerateGeometry::Scene_020_GenerateGeometry(): totalTime(0) {

}

Scene_020_GenerateGeometry::~Scene_020_GenerateGeometry() {
    clean();
}

void Scene_020_GenerateGeometry::setGame(Game *_game) {
    game = _game;
}

void Scene_020_GenerateGeometry::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_020_GenerateGeometry::pause() {
}

void Scene_020_GenerateGeometry::resume() {
}

void Scene_020_GenerateGeometry::handleEvent(const InputState &inputState) {

}

void Scene_020_GenerateGeometry::load() {
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", SHADER_GEOM(SHADER_NAME), SHADER_ID(SHADER_NAME));

    static const GLfloat tetrahedron_verts[] =
    {
            0.000f,  0.000f,  1.000f,
            0.943f,  0.000f, -0.333f,
        -0.471f,  0.816f, -0.333f,
        -0.471f, -0.816f, -0.333f
    };

    static const GLushort tetrahedron_indices[] =
    {
        0, 1, 2,
        0, 2, 3,
        0, 3, 1,
        3, 2, 1
    };

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tetrahedron_verts) + sizeof(tetrahedron_indices), NULL, GL_STATIC_DRAW);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, 0, sizeof(tetrahedron_indices), tetrahedron_indices);
    glBufferSubData(GL_ELEMENT_ARRAY_BUFFER, sizeof(tetrahedron_indices), sizeof(tetrahedron_verts), tetrahedron_verts);

    glBindBuffer(GL_ARRAY_BUFFER, buffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (GLvoid*)sizeof(tetrahedron_indices));
    glEnableVertexAttribArray(0);

    glEnable(GL_CULL_FACE);
    // glDisable(GL_CULL_FACE);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));
}

void Scene_020_GenerateGeometry::update(float dt) {
    totalTime += dt;
}

void Scene_020_GenerateGeometry::draw()
{
    static const GLfloat black[] = {0.0f, 0.0f, 0.2f, 1.0f};
    static const GLfloat one = 1.0f;
    float f = totalTime * timeScale;

    glClearBufferfv(GL_COLOR, 0, black);
    glClearBufferfv(GL_DEPTH, 0, &one);


    proj = Matrix4::createPerspectiveFOV(45.0f, game->windowWidth, game->windowHeight, 0.1f, 1000.0f);
    view = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -8.0f)) *
                            Matrix4::createRotationY(f * 71.0f) *
                            Matrix4::createRotationX(f * 10.0f);

    shader.use();
    shader.setMatrix4("mvpMatrix", proj * view);
    shader.setMatrix4("mvMatrix", view);
    shader.setFloat("stretch", sinf(f * 4.0f) * 0.75f + 1.0f);

    glBindVertexArray(vao);
    glDrawElements(GL_TRIANGLES, 12, GL_UNSIGNED_SHORT, NULL);
}
