//
// Created by gaetz on 28/08/2020.
//
#include "Scene_014_IndirectDrawAstroids.h"
#include "../engine/Game.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"
#include "../engine/Log.h"
//#include PATH(SCENE_NAME, EXT)

#include <cstdlib>
#include <GL/glew.h>

constexpr int NUM_DRAWS = 50000;

Scene_014_IndirectDrawAstroids::Scene_014_IndirectDrawAstroids() {}

Scene_014_IndirectDrawAstroids::~Scene_014_IndirectDrawAstroids() {
    clean();
}

void Scene_014_IndirectDrawAstroids::setGame(Game *_game) {
    game = _game;
}

void Scene_014_IndirectDrawAstroids::load() {
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", "", SHADER_ID(SHADER_NAME));

    object.load("assets/meshes/asteroids.sbm");
    mode = Mode::MODE_MULTIDRAW;
    paused = false;
    vsync = false;
    t = 0;

    glGenBuffers(1, &indirectDrawBuffer);
    glBindBuffer(GL_DRAW_INDIRECT_BUFFER, indirectDrawBuffer);
    glBufferData(GL_DRAW_INDIRECT_BUFFER,
                 NUM_DRAWS * sizeof(DrawArraysIndirectCommand),
                 NULL,
                 GL_STATIC_DRAW);

    DrawArraysIndirectCommand * cmd = (DrawArraysIndirectCommand*) glMapBufferRange(GL_DRAW_INDIRECT_BUFFER,
                                                                                    0,
                                                                                    NUM_DRAWS * sizeof(DrawArraysIndirectCommand),
                                                                                    GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT);
    
    for (int i = 0; i < NUM_DRAWS; i++)
    {
        object.getSubObjectInfo(i % object.getSubObjectCount(),
                                   cmd[i].first,
                                   cmd[i].count);
        cmd[i].primCount = 1;
        cmd[i].baseInstance = i;
    }

    glUnmapBuffer(GL_DRAW_INDIRECT_BUFFER);

    glBindVertexArray(object.getVao());
    glGenBuffers(1, &drawIndexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, drawIndexBuffer);
    glBufferData(GL_ARRAY_BUFFER,
                 NUM_DRAWS * sizeof(GLuint),
                 NULL,
                 GL_STATIC_DRAW);

    GLuint * drawIndex =
        (GLuint *)glMapBufferRange(GL_ARRAY_BUFFER,
                                   0,
                                   NUM_DRAWS * sizeof(GLuint),
                                   GL_MAP_WRITE_BIT |
                                   GL_MAP_INVALIDATE_BUFFER_BIT);

    for (int i = 0; i < NUM_DRAWS; i++)
    {
        drawIndex[i] = i;
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);

    glVertexAttribIPointer(10, 1, GL_UNSIGNED_INT, 0, NULL);
    glVertexAttribDivisor(10, 1);
    glEnableVertexAttribArray(10);

    projection = Matrix4::createPerspectiveFOV(50.0f, game->windowWidth, game->windowHeight, 1.0f, 2000.0f);
    shader = Assets::getShader(SHADER_ID(SHADER_NAME));
    shader.use();
}

void Scene_014_IndirectDrawAstroids::clean() {

}

void Scene_014_IndirectDrawAstroids::pause() {
}

void Scene_014_IndirectDrawAstroids::resume() {
}

void Scene_014_IndirectDrawAstroids::handleEvent(const InputState &inputState) {
    
}

void Scene_014_IndirectDrawAstroids::update(float dt) {
    int j;
    static const float one = 1.0f;
    static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };

    t += dt;

    view = Matrix4::createLookAt(Vector3(100.0f * Maths::cos(t * 0.023f), 100.0f * Maths::cos(t * 0.023f), 300.0f * Maths::sin(t * 0.037f) - 600.0f), 
                                Vector3(0.0f, 0.0f, 260.0f), 
                                Vector3::normalize(Vector3(0.1f - Maths::cos(t * 0.1f) * 0.3f, 1.0f, 0.0f)));

    shader.use();
    shader.setFloat("time", t);
    shader.setMatrix4("view_matrix", view);
    shader.setMatrix4("proj_matrix", projection);
    shader.setMatrix4("viewproj_matrix", projection * view);
}

void Scene_014_IndirectDrawAstroids::draw() 
{
    static const float one = 1.0f;
    static const float black[] = { 0.0f, 0.0f, 0.0f, 0.0f };
    glClearBufferfv(GL_COLOR, 0, black);
    glClearBufferfv(GL_DEPTH, 0, &one);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);

    glEnable(GL_CULL_FACE);

    glBindVertexArray(object.getVao());

    if (mode == Mode::MODE_MULTIDRAW)
    {
        glMultiDrawArraysIndirect(GL_TRIANGLES, NULL, NUM_DRAWS, 0);
    }
    else if (mode == Mode::MODE_SEPARATE_DRAWS)
    {
        for (int j = 0; j < NUM_DRAWS; j++)
        {
            GLuint first, count;
            object.getSubObjectInfo(j % object.getSubObjectCount(), first, count);
            glDrawArraysInstancedBaseInstance(GL_TRIANGLES,
                                              first,
                                              count,
                                              1, j);
        }
    }
}

