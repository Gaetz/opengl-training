#ifndef Scene_022_ComputeShaderPrefixSum_H
#define Scene_022_ComputeShaderPrefixSum_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"
#include "../engine/MeshObject.h"

constexpr int WORKGROUP_SIZE = 256;
constexpr int NUM_WORKGROUPS = 64;
constexpr int FLOCK_SIZE = (NUM_WORKGROUPS * WORKGROUP_SIZE);

struct flock_member
{
    Vector3 position;
    unsigned int : 32;
    Vector3 velocity;
    unsigned int : 32;
};

class Scene_023_ComputeShaderBoids : public Scene {
public:
    Scene_023_ComputeShaderBoids();
    ~Scene_023_ComputeShaderBoids();
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
    float totalTime;

    ComputeShader computeShader;
    Shader renderShader;

    GLuint flockBuffer[2];
    GLuint flockRenderVao[2];
    GLuint geometryBuffer;
    GLuint frameIndex;
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
