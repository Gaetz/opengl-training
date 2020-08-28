//
// Created by gaetz on 28/08/2020.
//

#ifndef Scene_009_Textures_H
#define Scene_009_Textures_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"


class Scene_009_Textures : public Scene {
public:
    Scene_009_Textures();
    ~Scene_009_Textures();
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
    Matrix4 transform[24];
    Matrix4 projection;

    Shader shader;
};


#endif //Scene_009_Textures_H
