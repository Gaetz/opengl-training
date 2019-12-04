#ifndef SPRITE_H
#define SPRITE_H 

#include <string>

#include "spritebatch.h"
#include "math_core.h"

class Sprite
{
public:
    Sprite();
    ~Sprite();

    void draw(Spritebatch& spritebatch);
private:
    Vector2 position;
    float angle;
    std::string textureName;
};

#endif