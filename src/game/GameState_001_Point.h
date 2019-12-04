//
// Created by gaetz on 04/12/2019.
//

#ifndef RENDLARGENT_GAMESTATE_001_POINT_H
#define RENDLARGENT_GAMESTATE_001_POINT_H

#include "../engine/gamestate.h"
#include "../engine/resource_manager.h"


class GameState_001_Point : public GameState {
public:
    GameState_001_Point();
    ~GameState_001_Point();
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


#endif //RENDLARGENT_GAMESTATE_001_POINT_H
