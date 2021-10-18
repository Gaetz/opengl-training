#include "Pacman.h"

Pacman::Pacman() : Cube(Vector2::zero, YELLOW) {

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

    switch (direction)
    {
    case 8:
        pos.y -= SPEED * dt;
        break;
    case 2:
        pos.y += SPEED * dt;
        break;
    case 4:
        pos.x -= SPEED * dt;
        break;
    case 6:
        pos.x += SPEED * dt;
        break;
    default:
        break;
    }

    updateTransform();
}

void Pacman::updateTransform() {
    Matrix4 translationOffset = Matrix4::createTranslation(Vector3(GRID_X_OFFSET + pos.x / 2.0f, 0.0f, GRID_Z_OFFSET + pos.y / 2.0f));
    transform = translationOffset;
}

