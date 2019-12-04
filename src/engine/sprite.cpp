#include "sprite.h"
#include "resource_manager.h"

Sprite::Sprite() : position(Vector2(0.f, 0.f)), angle(0.f), textureName("wall")
{}

Sprite::~Sprite()
{}

void Sprite::draw(Spritebatch& spritebatch)
{
    Vector4 rect = Vector4(position.x, position.y, 10.0f, 10.0f);
    Vector4 uvRect = Vector4(0.f, 0.f, 1.f, 1.f);
    ColorRGBA8 color = ColorRGBA8(255, 255, 255, 255);
    Texture2D tex = ResourceManager::getTexture(textureName);
    spritebatch.draw(rect, uvRect, tex.id, 0.0f, color);
}
