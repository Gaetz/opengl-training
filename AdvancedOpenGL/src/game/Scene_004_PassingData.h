//
// Created by gaetz on 04/12/2019.
//

#ifndef Scene_004_Tessellation_H
#define Scene_004_Tessellation_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"
#include "../engine/Color.h"


class Scene_004_PassingData : public Scene {
public:
    Scene_004_PassingData();
    ~Scene_004_PassingData();
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

    float timeSinceStart;
    Color displayColor;
};


#endif //Scene_004_Tessellation_H
