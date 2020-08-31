//
// Created by gaetz on 28/08/2020.
//

#ifndef Scene_011_MipmapTunnel_H
#define Scene_011_MipmapTunnel_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"
#include "../engine/MeshObject.h"

class Scene_011_MipmapTunnel : public Scene {
public:
    Scene_011_MipmapTunnel();
    ~Scene_011_MipmapTunnel();
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
    GLuint texFloor, texWall, texCeiling;
    Matrix4 transform[4];
    Matrix4 projection;
};


#endif //Scene_011_MipmapTunnel_H
