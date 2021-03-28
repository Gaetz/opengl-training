//
// Created by gaetz on 04/12/2019.
//

#ifndef Scene_015_TessellationModes_H
#define Scene_015_TessellationModes_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"


class Scene_015_TessellationModes : public Scene {
public:
    Scene_015_TessellationModes();
    ~Scene_015_TessellationModes();
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


#endif //Scene_015_TessellationModes_H
