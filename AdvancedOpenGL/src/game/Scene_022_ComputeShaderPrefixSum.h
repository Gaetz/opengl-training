#ifndef Scene_022_ComputeShaderPrefixSum_H
#define Scene_022_ComputeShaderPrefixSum_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"
#include "../engine/MeshObject.h"

constexpr int NUM_ELEMENTS = 2048;

class Scene_022_ComputeShaderPrefixSum : public Scene {
public:
    Scene_022_ComputeShaderPrefixSum();
    ~Scene_022_ComputeShaderPrefixSum();
    void load();
    void clean();
    void pause();
    void resume();
    void handleEvent(const InputState &);
    void update(float dt);
    void draw();
    void setGame(Game *);

private:
    Game *game;

    GLuint dataBuffer[2];
    float inputData[NUM_ELEMENTS];
    float outputData[NUM_ELEMENTS];
    ComputeShader cShader;

    void prefixSum(const float * input, float * output, int elements);
};

static inline float randomFloat()
{
    static unsigned int seed = 0x13371337;

    float res;
    unsigned int tmp;

    seed *= 16807;
    tmp = seed ^ (seed >> 4) ^ (seed << 15);
    *((unsigned int *) &res) = (tmp >> 9) | 0x3F800000;

    return (res - 1.0f);
}


#endif //Scene_022_ComputeShaderPrefixSum_H
