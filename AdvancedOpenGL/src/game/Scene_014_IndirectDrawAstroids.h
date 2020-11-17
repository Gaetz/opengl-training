//
// Created by gaetz on 28/08/2020.
//

#ifndef Scene_014_IndirectDrawAstroids_H
#define Scene_014_IndirectDrawAstroids_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"
#include "../engine/MeshObject.h"

struct DrawArraysIndirectCommand
{
    GLuint count;
    GLuint primCount;
    GLuint first;
    GLuint baseInstance;
};

enum class Mode
{
    MODE_FIRST,
    MODE_MULTIDRAW = 0,
    MODE_SEPARATE_DRAWS,
    MODE_MAX = MODE_SEPARATE_DRAWS
};

class Scene_014_IndirectDrawAstroids : public Scene
{
public:
    Scene_014_IndirectDrawAstroids();
    ~Scene_014_IndirectDrawAstroids();
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

    MeshObject object;
    GLuint indirectDrawBuffer;
    GLuint drawIndexBuffer;
    Mode mode;
    bool paused;
    bool vsync;
    float t;

    Matrix4 view;
    Matrix4 projection;
};

#endif //Scene_014_IndirectDrawAstroids_H
