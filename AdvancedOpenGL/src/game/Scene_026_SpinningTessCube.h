//
// Created by gaetz on 04/12/2019.
//

#ifndef Scene_026_SpinningTessCube_H
#define Scene_026_SpinningTessCube_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"

#include "CubeObject.h"

class CubeMesh;

class Scene_026_SpinningTessCube : public Scene {
public:
    Scene_026_SpinningTessCube();
    ~Scene_026_SpinningTessCube();
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
    CubeMesh* cubeMesh;

    Matrix4 projection;
    Shader shader;

    vector<CubeObject> cubes;
    float newXPosition { 0 };
};


#endif //Scene_026_SpinningTessCube_H
