//
// Created by gaetz on 04/12/2019.
//

#ifndef Scene_016_TerrainRendering_H
#define Scene_016_TerrainRendering_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"


class Scene_016_TerrainRendering : public Scene {
public:
    Scene_016_TerrainRendering();
    ~Scene_016_TerrainRendering();
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
    GLuint vao;
    GLuint buffer;

    // Uniforms
    Matrix4 mvp;
    Matrix4 view;
    Matrix4 proj;
    float dmapDepth;
    bool isFogEnabled;

    GLuint texDisplacement;
    GLuint texColor;
    bool isDisplacementEnabled;
    bool wireframe;
    bool paused;

    float totalTime;
    float t, r, h;

    Shader shader;
};


#endif //Scene_016_TerrainRendering_H
