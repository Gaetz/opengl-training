//
// Created by gaetz on 04/12/2019.
//

#ifndef Scene_017_CubicBezierPatches_H
#define Scene_017_CubicBezierPatches_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"


class Scene_017_CubicBezierPatches : public Scene {
public:
    Scene_017_CubicBezierPatches();
    ~Scene_017_CubicBezierPatches();
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
    GLuint cageIndices;
    Vector3 patchData[16];

    bool showPoints;
    bool showCage;
    bool wireframe;
    bool paused;

    float totalTime;
    float t;
    float timeScale = 0.05f;
    float morphScale = 50.0f;

    Shader shader;
    Shader controlPointsShader;
};


#endif //Scene_017_CubicBezierPatches_H
