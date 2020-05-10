#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"

SpriteComponent::SpriteComponent(Actor& ownerP, Texture& textureP, int drawOrderP):
	Component(ownerP),
	texture(textureP), 
	drawOrder(drawOrderP), 
	texWidth(textureP.getWidth()),
	texHeight(textureP.getHeight())
{
	owner.getGame().addSprite(this);
}

SpriteComponent::~SpriteComponent()
{
	owner.getGame().removeSprite(this);
}

void SpriteComponent::setTexture(const Texture& textureP)
{
	texture = textureP;
	texture.updateInfo(texWidth, texHeight);
}

void SpriteComponent::draw(Renderer& renderer)
{
	Vector2 origin{ texWidth / 2.f, texHeight / 2.f };
	renderer.drawSprite(
		owner.getPosition(),
		owner.getRotation(),
		owner.getScale(),
		texture,
		Rectangle::nullRect,
		origin,
		Renderer::Flip::None
	);
}

