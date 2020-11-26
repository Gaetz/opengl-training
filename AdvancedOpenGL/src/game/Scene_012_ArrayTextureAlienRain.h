#ifndef Scene_012_ArrayTextureAlienRain_H
#define Scene_012_ArrayTextureAlienRain_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"
#include "../engine/MeshObject.h"

class Scene_012_ArrayTextureAlienRain : public Scene {
public:
    Scene_012_ArrayTextureAlienRain();
    ~Scene_012_ArrayTextureAlienRain();
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
    Shader shader;
    GLuint vao;
    GLuint texAliens;
    GLuint rainBuffer;
    float dropletXOffset[256];
    float dropletRotSpeed[256];
    float dropletFallSpeed[256];

    Matrix4 transform[4];
    Matrix4 projection;
};

static unsigned int seed = 0x13371337;
static inline float randomFloat()
{
    float res;
    unsigned int tmp;

    seed *= 16807;
    tmp = seed ^ (seed >> 4) ^ (seed << 15);
    *((unsigned int *) &res) = (tmp >> 9) | 0x3F800000;

    return (res - 1.0f);
}

#endif //Scene_012_ArrayTextureAlienRain_H
