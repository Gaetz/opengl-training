//
// Created by gaetz on 04/12/2019.
//

#ifndef Scene_019_ModifyGeometry_H
#define Scene_019_ModifyGeometry_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"
#include "../engine/MeshObject.h"

class Scene_019_ModifyGeometry : public Scene {
public:
    Scene_019_ModifyGeometry();
    ~Scene_019_ModifyGeometry();
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
    MeshObject object;
    float totalTime;

    // Uniforms
    Matrix4 mvp;
    Matrix4 view;
    Matrix4 proj;

    Shader shader;
};


#endif //Scene_019_ModifyGeometry_H
