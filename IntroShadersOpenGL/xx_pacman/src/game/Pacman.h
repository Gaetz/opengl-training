#ifndef PACMAN_H
#define PACMAN_H

#include "Cube.h"
#include "../engine/InputState.h"

constexpr float SPEED { 10.0f };

class Pacman : public Cube {
public:
    Pacman();
    void update(float dt, const InputState& inputState);
    void updateTransform() override;
private:
    // 8 is up, 6 is right, 2 is down, 4 is left. 0 is stop.
    int direction { 0 };
};

#endif