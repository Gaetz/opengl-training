//
// Created by gaetz on 04/12/2019.
//

#ifndef Scene_005_Tessellation_H
#define Scene_005_Tessellation_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"


class Scene_005_Tessellation : public Scene {
public:
    Scene_005_Tessellation();
    ~Scene_005_Tessellation();
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


#endif //Scene_005_Tessellation_H
