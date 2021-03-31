//
// Created by gaetz on 04/12/2019.
//

#ifndef Scene_020_GenerateGeometry_H
#define Scene_020_GenerateGeometry_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"
#include "../engine/MeshObject.h"

class Scene_020_GenerateGeometry : public Scene {
public:
    Scene_020_GenerateGeometry();
    ~Scene_020_GenerateGeometry();
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

    // Uniforms
    Matrix4 mvp;
    Matrix4 view;
    Matrix4 proj;

    Shader shader;
};


#endif //Scene_020_GenerateGeometry_H
