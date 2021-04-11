#include "Scene_022_ComputeShaderPrefixSum.h"
#include "../engine/Timer.h"
#include "../engine/MacroUtils.h"
#include "../engine/Log.h"

#include <cstdlib>
#include <ctime>
#include <GL/glew.h>


Scene_022_ComputeShaderPrefixSum::Scene_022_ComputeShaderPrefixSum() {

}

Scene_022_ComputeShaderPrefixSum::~Scene_022_ComputeShaderPrefixSum() {
    clean();
}

void Scene_022_ComputeShaderPrefixSum::setGame(Game *_game) {
    game = _game;
}

void Scene_022_ComputeShaderPrefixSum::clean() {

}

void Scene_022_ComputeShaderPrefixSum::pause() {
}

void Scene_022_ComputeShaderPrefixSum::resume() {
}

void Scene_022_ComputeShaderPrefixSum::handleEvent(const InputState &inputState) {

}

void Scene_022_ComputeShaderPrefixSum::load() {
    Assets::loadComputeShader(SHADER_COMP(SHADER_NAME), SHADER_ID(SHADER_NAME));

    glGenBuffers(2, dataBuffer);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, dataBuffer[0]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_ELEMENTS * sizeof(float), NULL, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_SHADER_STORAGE_BUFFER, dataBuffer[1]);
    glBufferData(GL_SHADER_STORAGE_BUFFER, NUM_ELEMENTS * sizeof(float), NULL, GL_DYNAMIC_COPY);

    int i;

    for (i = 0; i < NUM_ELEMENTS; i++)
    {
        inputData[i] = randomFloat();
    }

    prefixSum(inputData, outputData, NUM_ELEMENTS);

    cShader = Assets::getComputeShader(SHADER_ID(SHADER_NAME));

    int n;
    glGetIntegerv(GL_MAX_SHADER_STORAGE_BUFFER_BINDINGS, &n);


    glShaderStorageBlockBinding(cShader.id, 0, 0);
    glShaderStorageBlockBinding(cShader.id, 1, 1);
}

void Scene_022_ComputeShaderPrefixSum::update(float dt) {
    float * ptr;

    glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 0, dataBuffer[0], 0, sizeof(float) * NUM_ELEMENTS);
    glBufferSubData(GL_SHADER_STORAGE_BUFFER, 0, sizeof(float) * NUM_ELEMENTS, inputData);

    glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 1, dataBuffer[1], 0, sizeof(float) * NUM_ELEMENTS);

    cShader.use();
    glDispatchCompute(1, 1, 1);

    glMemoryBarrier(GL_SHADER_STORAGE_BARRIER_BIT);
    glFinish();

    glBindBufferRange(GL_SHADER_STORAGE_BUFFER, 0, dataBuffer[1], 0, sizeof(float) * NUM_ELEMENTS);
    ptr = (float *)glMapBufferRange(GL_SHADER_STORAGE_BUFFER, 0, sizeof(float) * NUM_ELEMENTS, GL_MAP_READ_BIT);

    char buffer[1024];
    sprintf(buffer, "SUM: %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f "
                    "%2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f %2.2f",
                    ptr[0], ptr[1], ptr[2], ptr[3], ptr[4], ptr[5], ptr[6], ptr[7],
                    ptr[8], ptr[9], ptr[10], ptr[11], ptr[12], ptr[13], ptr[14], ptr[15]);

    LOG(Info) << buffer;

    glUnmapBuffer(GL_SHADER_STORAGE_BUFFER);
}

void Scene_022_ComputeShaderPrefixSum::draw()
{

}

void Scene_022_ComputeShaderPrefixSum::prefixSum(const float * input, float * output, int elements)
{
    float f = 0.0f;
    int i;

    for (i = 0; i < elements; i++)
    {
        f += input[i];
        output[i] = f;
    }
}