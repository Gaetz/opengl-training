//
// Created by gaetz on 04/12/2019.
//

#ifndef SCENE_002_POINT_H
#define SCENE_002_POINT_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"


class Scene_002_Point : public Scene {
public:
    Scene_002_Point();
    ~Scene_002_Point();
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
    Shader shader;
};


#endif //SCENE_002_POINT_H
