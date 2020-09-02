//
// Created by gaetz on 28/08/2020.
//

#ifndef Scene_013_InstancedGrassBlades_H
#define Scene_013_InstancedGrassBlades_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"
#include "../engine/MeshObject.h"

class Scene_013_InstancedGrassBlades : public Scene {
public:
    Scene_013_InstancedGrassBlades();
    ~Scene_013_InstancedGrassBlades();
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
    GLuint buffer;
    GLuint texGrassColor;
    GLuint texGrassLength;
    GLuint texGrassOrientation;
    GLuint texGrassBend;

    Matrix4 view;
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

#endif //Scene_013_InstancedGrassBlades_H
