//
// Created by gaetz on 28/08/2020.
//

#ifndef Scene_010_TextureCoordinates_H
#define Scene_010_TextureCoordinates_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"
#include "../engine/MeshObject.h"

class Scene_010_TextureCoordinates : public Scene {
public:
    Scene_010_TextureCoordinates();
    ~Scene_010_TextureCoordinates();
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
    GLuint texObject[2];
    GLuint texIndex;
    Matrix4 transform;
    Matrix4 projection;
    MeshObject object;
};


#endif //Scene_010_TextureCoordinates_H
