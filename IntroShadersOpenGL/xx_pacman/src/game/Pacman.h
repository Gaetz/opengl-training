#ifndef PACMAN_H
#define PACMAN_H

#include "Cube.h"
#include "Constants.h"
#include "../engine/InputState.h"
#include "Level.h"

class Pacman : public Cube {
public:
    Pacman(const Level& level);
    void update(float dt, const InputState& inputState);
    void updateTransform() override;

protected:
    const Level& level;
    // 8 is up, 6 is right, 2 is down, 4 is left. 0 is stop.
    int direction { 0 };

    Vector2 computeNextTilePos(int direction);
    Vector2 computeTilePos(const Vector3& pos);
    Vector3 computeCleanPos(const Vector2& tilePos);
    void updateMoveWithCollisions(const Vector3& nextPos, const Vector2& nextTilePos);
};

#endif