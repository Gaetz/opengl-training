#include "Scene_025_ComputeShaderBoids.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"
#include "../engine/Log.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_025_ComputeShaderBoids::Scene_025_ComputeShaderBoids() : totalTime(0), frameIndex(0) {

}

Scene_025_ComputeShaderBoids::~Scene_025_ComputeShaderBoids() {
    clean();
}

void Scene_025_ComputeShaderBoids::setGame(Game *_game) {
    game = _game;
}

void Scene_025_ComputeShaderBoids::clean() {

}

void Scene_025_ComputeShaderBoids::pause() {
}

void Scene_025_ComputeShaderBoids::resume() {
}

void Scene_025_ComputeShaderBoids::handleEvent(const InputState &inputState) {

}

void Scene_025_ComputeShaderBoids::load() {
    Assets::loadComputeShader(SHADER_COMP(SHADER_NAME), SHADER_ID(SHADER_NAME));
    Assets::loadShader(SHADER_VERT(SHADER_NAME), SHADER_FRAG(SHADER_NAME), "", "", "", SHADER_ID(SHADER_NAME));

    // This is position and normal data for a paper airplane
    static const Vector3 geometry[] =
    {
        // Positions
        Vector3(-5.0f, 1.0f, 0.0f),
        Vector3(-1.0f, 1.5f, 0.0f),
        Vector3(-1.0f, 1.5f, 7.0f),
        Vector3(0.0f, 0.0f, 0.0f),
        Vector3(0.0f, 0.0f, 10.0f),
        Vector3(1.0f, 1.5f, 0.0f),
        Vector3(1.0f, 1.5f, 7.0f),
        Vector3(5.0f, 1.0f, 0.0f),

        // Normals
        Vector3(0.0f, 0.0f, 0.0f),
        Vector3(0.0f, 0.0f, 0.0f),
        Vector3(0.107f, -0.859f, 0.00f),
        Vector3(0.832f, 0.554f, 0.00f),
        Vector3(-0.59f, -0.395f, 0.00f),
        Vector3(-0.832f, 0.554f, 0.00f),
        Vector3(0.295f, -0.196f, 0.00f),
        Vector3(0.124f, 0.992f, 0.00f),
    };

    computeShader = Assets::getComputeShader(SHADER_ID(SHADER_NAME));
    renderShader = Assets::getShader(SHADER_ID(SHADER_NAME));

    glGenBuffers(2, flockBuffer);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, flockBuffer[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, FLOCK_SIZE * sizeof(FlockMember), NULL, GL_DYNAMIC_COPY);
    glBindBuffer(GL_SHADER_STORAGE_BUFFER, flockBuffer[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, FLOCK_SIZE * sizeof(FlockMember), NULL, GL_DYNAMIC_COPY);

    int i;

    glGenBuffers(1, &geometryBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, geometryBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(geometry), geometry, GL_STATIC_DRAW);

    glGenVertexArrays(2, flockRenderVao);

    for (i = 0; i < 2; i++)
    {
        glBindVertexArray(flockRenderVao[i]);
        glBindBuffer(GL_ARRAY_BUFFER, geometryBuffer);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, (void *)(8 * sizeof(Vector3)));

        glBindBuffer(GL_ARRAY_BUFFER, flockBuffer[i]);
        glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(FlockMember), NULL);
        glVertexAttribPointer(3, 3, GL_FLOAT, GL_FALSE, sizeof(FlockMember), (void *)sizeof(Vector4));
        glVertexAttribDivisor(2, 1);
        glVertexAttribDivisor(3, 1);

        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);
        glEnableVertexAttribArray(2);
        glEnableVertexAttribArray(3);
    }

    glBindBuffer(GL_ARRAY_BUFFER, flockBuffer[0]);
    FlockMember * ptr = reinterpret_cast<FlockMember *>(
        glMapBufferRange(GL_ARRAY_BUFFER, 0, FLOCK_SIZE * sizeof(FlockMember), 
                         GL_MAP_WRITE_BIT | GL_MAP_INVALIDATE_BUFFER_BIT)
    );

    for (i = 0; i < FLOCK_SIZE; i++)
    {
        ptr[i].position = (Vector3(randomFloat(), randomFloat(), randomFloat()) - Vector3(0.5f, 0.5f, 0.5f)) * 300.0f;
        ptr[i].velocity = (Vector3(randomFloat(), randomFloat(), randomFloat()) - Vector3(0.5f, 0.5f, 0.5f));
    }

    glUnmapBuffer(GL_ARRAY_BUFFER);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
}

void Scene_025_ComputeShaderBoids::update(float dt) {
    totalTime += dt;

    computeShader.use();
    Vector3 goal = Vector3(sinf(totalTime * 0.34f), cosf(totalTime * 0.29f), sinf(totalTime * 0.12f) * cosf(totalTime * 0.5f));

    goal = goal * Vector3(35.0f, 25.0f, 60.0f);

    computeShader.setVector3f("goal", goal);

    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 0, flockBuffer[frameIndex]);
    glBindBufferBase(GL_SHADER_STORAGE_BUFFER, 1, flockBuffer[frameIndex ^ 1]);

    glDispatchCompute(NUM_WORKGROUPS, 1, 1);
}

void Scene_025_ComputeShaderBoids::draw()
{
    renderShader.use();

    Matrix4 mv_matrix = Matrix4::createLookAt(Vector3(0.0f, 0.0f, -200.0f),
                                            Vector3(0.0f, 0.0f, 0.0f),
                                            Vector3(0.0f, 1.0f, 0.0f));
    Matrix4 proj_matrix = Matrix4::createPerspectiveFOV(60.0f, game->windowWidth, game->windowHeight, 0.1f, 3000.0f);
    Matrix4 mvp = proj_matrix * mv_matrix;

    renderShader.setMatrix4("mvp", mvp);

    glBindVertexArray(flockRenderVao[frameIndex]);
    glDrawArraysInstanced(GL_TRIANGLE_STRIP, 0, 8, FLOCK_SIZE);

    frameIndex ^= 1;
}
