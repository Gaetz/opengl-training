//
// Created by gaetz on 04/12/2019.
//

#ifndef Scene_021_ChangePrimitiveType_H
#define Scene_021_ChangePrimitiveType_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"
#include "../engine/MeshObject.h"

class Scene_021_ChangePrimitiveType : public Scene {
public:
    Scene_021_ChangePrimitiveType();
    ~Scene_021_ChangePrimitiveType();
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
    float totalTime;
    const float timeScale = 0.05f;
    MeshObject object;

    // Uniforms
    Matrix4 mvp;
    Matrix4 view;
    Matrix4 proj;

    Shader shader;
};


#endif //Scene_021_ChangePrimitiveType_H
