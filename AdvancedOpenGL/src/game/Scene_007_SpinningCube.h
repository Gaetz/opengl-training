//
// Created by gaetz on 04/12/2019.
//

#ifndef Scene_007_SpinningCube_H
#define Scene_007_SpinningCube_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"

class Scene_007_SpinningCube : public Scene {
public:
    Scene_007_SpinningCube();
    ~Scene_007_SpinningCube();
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
    Matrix4 transform;
    Matrix4 projection;

    Shader shader;
};


#endif //Scene_007_SpinningCube_H
