//
// Created by gaetz on 04/12/2019.
//

#ifndef SCENE_001_COLOR_H
#define SCENE_001_COLOR_H

#include "../engine/Scene.h"
#include "../engine/Assets.h"


class Scene_001_Color : public Scene {
public:
    Scene_001_Color();
    ~Scene_001_Color();
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
};


#endif //SCENE_001_COLOR_H
