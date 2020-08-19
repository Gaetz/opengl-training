#include "SpriteComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Rectangle.h"
#include "LevelLoader.h"
#include "Assets.h"

SpriteComponent::SpriteComponent(Actor* ownerP, Texture* textureP, int drawOrderP):
	Component(ownerP),
	texture(textureP), 
	drawOrder(drawOrderP), 
	texWidth(0),
	texHeight(0),
	isVisible(true)
{
	owner.getGame().getRenderer().addSprite(this);
	if (textureP != nullptr)
	{
		setTexture(*textureP);
	}
}

SpriteComponent::~SpriteComponent()
{
	owner.getGame().getRenderer().removeSprite(this);
}

void SpriteComponent::setTexture(Texture& textureP)
{
	texture = &textureP;
	texture->updateInfo(texWidth, texHeight);
}

void SpriteComponent::draw(IRenderer& renderer)
{
	Vector2 origin{ texWidth / 2.f, texHeight / 2.f };
	renderer.drawSprite(owner, *texture, Rectangle::nullRect, origin, IRenderer::Flip::None);
}

void SpriteComponent::setVisible(bool isVisibleP)
{
	isVisible = isVisibleP;
}

void SpriteComponent::loadProperties(const rapidjson::Value& inObj)
{
	Component::loadProperties(inObj);

	std::string texFile;
	if (JsonHelper::getString(inObj, "textureFile", texFile))
	{
		setTexture(Assets::getTexture(texFile));
	}

	JsonHelper::getInt(inObj, "drawOrder", drawOrder);
	JsonHelper::getBool(inObj, "visible", isVisible);
}

void SpriteComponent::saveProperties(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObj) const
{
	Component::saveProperties(alloc, inObj);

	if (texture)
	{
		JsonHelper::addString(alloc, inObj, "textureFile", texture->getName());
	}

	JsonHelper::addInt(alloc, inObj, "drawOrder", drawOrder);
	JsonHelper::addBool(alloc, inObj, "visible", isVisible);
}

