#include "Pacman.h"

Pacman::Pacman(const Level& levelP) :
    Cube(Vector2::zero, YELLOW),
    level {levelP}
{
    pos = Vector3 { 1.0f, 0.0f, 1.0f };
    tilePos = Vector2 { 1.0f, 1.0f };
}

void Pacman::update(float dt, const InputState& inputState) {
    if(inputState.up) {
        direction = 8;
    } else if(inputState.right) {
        direction = 6;
    } else if(inputState.down) {
        direction = 2;
    } else if(inputState.left) {
        direction = 4;
    }


    Vector3 nextPos;
    Vector2 nextTilePos = computeNextTilePos(direction);
    switch (direction)
    {
    case 8:
        nextPos = Vector3 { pos.x, pos.y, pos.z - SPEED * dt };
        updateMoveWithCollisions(nextPos, nextTilePos);
        break;
    case 2:
        nextPos = Vector3 { pos.x, pos.y, pos.z + SPEED * dt };
        updateMoveWithCollisions(nextPos, nextTilePos);
        break;
    case 4:
        nextPos = Vector3 { pos.x - SPEED * dt, pos.y, pos.z };
        updateMoveWithCollisions(nextPos, nextTilePos);
        break;
    case 6:
        nextPos = Vector3 { pos.x + SPEED * dt, pos.y, pos.z };
        updateMoveWithCollisions(nextPos, nextTilePos);
        break;
    default:
        break;
    }

    updateTransform();
}

void Pacman::updateTransform() {
    Matrix4 translationOffset = Matrix4::createTranslation(Vector3(GRID_X_OFFSET + pos.x / 2.0f, 0.0f, GRID_Z_OFFSET + pos.z / 2.0f));
    transform = translationOffset;
}

Vector2 Pacman::computeNextTilePos(int direction) {
    switch (direction)
    {
    case 8:
        return tilePos - Vector2::unitY;
    case 2:
        return tilePos + Vector2::unitY;
    case 4:
        return tilePos - Vector2::unitX;
    case 6:
        return tilePos + Vector2::unitX;
    default:
        return tilePos;
    }
}

Vector2 Pacman::computeTilePos(const Vector3& pos) {
    return Vector2 { static_cast<float>(round(pos.x)), static_cast<float>(round(pos.z)) };
}

Vector3 Pacman::computeCleanPos(const Vector2& tilePos) {
    return Vector3 { tilePos.x, 0.0f, tilePos.y };
}

void Pacman::updateMoveWithCollisions(const Vector3& nextPos, const Vector2& nextTilePos) {
    // Next tile is a wall, so stop movement
    if(level.content[nextTilePos.y][nextTilePos.x] == TileContent::Wall) {
        direction = 0;
        pos = computeCleanPos(tilePos);
    }
    // No collision, just move
    else {
        pos = nextPos;
    }
    // Keep tilePos sync
    tilePos = computeTilePos(pos);
}



