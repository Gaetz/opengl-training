//
// Created by gaetz on 04/12/2019.
//

#ifndef SCENE_001_POINT_H
#define SCENE_001_POINT_H

#include "../engine/Scene.h"
#include "../engine/ResourceManager.h"


class Scene_001_Point : public Scene {
public:
    Scene_001_Point();
    ~Scene_001_Point();
    void load();
    void clean();
    void pause();
    void resume();
    void handleEvent(const InputState &);
    void update(unsigned int dt);
    void draw();
    void setGame(Game *);

private:
    Game *game;
};


#endif //SCENE_001_POINT_H
