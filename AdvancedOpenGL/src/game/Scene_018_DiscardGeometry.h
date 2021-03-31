//
// Created by gaetz on 04/12/2019.
//

#ifndef Scene_018_DiscardGeometry_H
#define Scene_018_DiscardGeometry_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"
#include "../engine/MeshObject.h"

class Scene_018_DiscardGeometry : public Scene {
public:
    Scene_018_DiscardGeometry();
    ~Scene_018_DiscardGeometry();
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
    const float timeScale = 0.01f;

    // Uniforms
    Matrix4 mvp;
    Matrix4 view;
    Matrix4 proj;

    Shader shader;
};


#endif //Scene_018_DiscardGeometry_H
