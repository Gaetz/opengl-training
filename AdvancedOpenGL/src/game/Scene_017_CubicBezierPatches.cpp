#include "Scene_017_CubicBezierPatches.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_017_CubicBezierPatches::Scene_017_CubicBezierPatches():
    wireframe(false), paused(false), totalTime(0),
    showCage(false), showPoints(false)
{
}

Scene_017_CubicBezierPatches::~Scene_017_CubicBezierPatches() {
    clean();
}

void Scene_017_CubicBezierPatches::setGame(Game *_game) {
    game = _game;
}

void Scene_017_CubicBezierPatches::clean() {
    glDeleteVertexArrays(1, &vao);
}

void Scene_017_CubicBezierPatches::pause() {
}

void Scene_017_CubicBezierPatches::resume() {
}

void Scene_017_CubicBezierPatches::handleEvent(const InputState &inputState) {
    if(inputState.keyboardState.isJustPressed(SDL_SCANCODE_W)) {
        wireframe = !wireframe;
    }
    if(inputState.keyboardState.isJustPressed(SDL_SCANCODE_P)) {
        paused = !paused;
    }
    if(inputState.keyboardState.isJustPressed(SDL_SCANCODE_Q)) {
        showCage = !showCage;
    }
    if(inputState.keyboardState.isJustPressed(SDL_SCANCODE_E)) {
        showPoints = !showPoints;
    }
}

void Scene_017_CubicBezierPatches::load() {
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), SHADER_TECS(SHADER_NAME), SHADER_TESE(SHADER_NAME), "", SHADER_ID(SHADER_NAME));
    Assets::loadShader("assets/shaders/017_ControlPoints.vert", "assets/shaders/017_ControlPoints.frag", "", "", "", "017_ControlPoints");

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);

    glGenBuffers(1, &buffer);
    glBindBuffer(GL_ARRAY_BUFFER, buffer);

    glBufferData(GL_ARRAY_BUFFER, sizeof(patchData), NULL, GL_DYNAMIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
    glEnableVertexAttribArray(0);

    static const GLushort indices[] =
    {
        0, 1, 1, 2, 2, 3,
        4, 5, 5, 6, 6, 7,
        8, 9, 9, 10, 10, 11,
        12, 13, 13, 14, 14, 15,

        0, 4, 4, 8, 8, 12,
        1, 5, 5, 9, 9, 13,
        2, 6, 6, 10, 10, 14,
        3, 7, 7, 11, 11, 15
    };

    glGenBuffers(1, &cageIndices);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, cageIndices);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    shader = Assets::getShader(SHADER_ID(SHADER_NAME));
    controlPointsShader = Assets::getShader("017_ControlPoints");
}

void Scene_017_CubicBezierPatches::update(float dt) {
    if (!paused)
        totalTime += dt;

    t = totalTime * timeScale;
}

void Scene_017_CubicBezierPatches::draw()
{
    // Bezier
    static const float patchInitializer[]
    {
        -1.0f,  -1.0f,  0.0f,
        -0.33f, -1.0f,  0.0f,
        0.33f, -1.0f,  0.0f,
        1.0f,  -1.0f,  0.0f,

        -1.0f,  -0.33f, 0.0f,
        -0.33f, -0.33f, 0.0f,
        0.33f, -0.33f, 0.0f,
        1.0f,  -0.33f, 0.0f,

        -1.0f,   0.33f, 0.0f,
        -0.33f,  0.33f, 0.0f,
        0.33f,  0.33f, 0.0f,
        1.0f,   0.33f, 0.0f,

        -1.0f,   1.0f,  0.0f,
        -0.33f,  1.0f,  0.0f,
        0.33f,  1.0f,  0.0f,
        1.0f,   1.0f,  0.0f,
    };

    static const GLfloat bgColor[] = {0.0f, 0.0f, 0.2f, 1.0f};
    static const GLfloat one = 1.0f;
    glClearBufferfv(GL_COLOR, 0, bgColor);
    glClearBufferfv(GL_DEPTH, 0, &one);

    glEnable(GL_DEPTH_TEST);

    Vector3* p = (Vector3 *)glMapBufferRange(GL_ARRAY_BUFFER, 0, sizeof(patchData), GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
    memcpy(p, patchInitializer, sizeof(patchInitializer));

    int i;
    for (i = 0; i < 16; i++)
    {
        float fi = (float)i / 16.0f;
        p[i].z = sinf(t * morphScale * (0.2f + fi * 0.3f));
        patchData[i] = p[i];
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);

    glBindVertexArray(vao);

    shader.use();

    proj = Matrix4::createPerspectiveFOV(45.0f, game->windowWidth, game->windowHeight, 1.0f, 1000.0f);
    view = Matrix4::createTranslation(Vector3(0.0f, 0.0f, -4.0f)) *
                            Matrix4::createRotationY(t * 10.0f) *
                            Matrix4::createRotationX(t * 17.0f);

    shader.use();
    shader.setMatrix4("mv_matrix", view);
    shader.setMatrix4("proj_matrix", proj);
    shader.setMatrix4("mvp", proj * view);

    if (wireframe)
        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    else
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

    glPatchParameteri(GL_PATCH_VERTICES, 16);
    glDrawArrays(GL_PATCHES, 0, 16);


    // Control points
    controlPointsShader.use();
    controlPointsShader.setMatrix4("mvp", proj * view);

    if (showPoints) {
        glPointSize(9.0f);
        controlPointsShader.setVector4f("draw_color", Vector4(0.2f, 0.7f, 0.9f, 1.0f));
        glDrawArrays(GL_POINTS, 0, 16);
    }

    if (showCage) {
        controlPointsShader.setVector4f("draw_color", Vector4(0.7f, 0.9f, 0.2f, 1.0f));
        glDrawElements(GL_LINES, 48, GL_UNSIGNED_SHORT, NULL);
    }

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}
