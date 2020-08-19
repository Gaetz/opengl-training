#include "BoxComponent.h"
#include "Actor.h"
#include "Game.h"
#include "LevelLoader.h"

BoxComponent::BoxComponent(Actor* ownerP, int updateOrderP):
	Component(ownerP, updateOrderP),
	objectBox(Vector3::zero, Vector3::zero),
	worldBox(Vector3::zero, Vector3::zero),
	shouldRotate(true)
{
	Game::instance().getPhysicsSystem().addBox(this);
}

BoxComponent::~BoxComponent()
{
	Game::instance().getPhysicsSystem().removeBox(this);
}

void BoxComponent::setObjectBox(const AABB& objectBoxP)
{
	objectBox = objectBoxP;
}

void BoxComponent::setShouldRotate(bool shouldRotateP)
{
	shouldRotate = shouldRotateP;
}

void BoxComponent::onUpdateWorldTransform()
{
	// Reset to object space box
	worldBox = objectBox;

	worldBox.min *= owner.getScale();
	worldBox.max *= owner.getScale();
	if (shouldRotate)
	{
		worldBox.rotate(owner.getRotation());
	}
	worldBox.min += owner.getPosition();
	worldBox.max += owner.getPosition();
}

void BoxComponent::loadProperties(const rapidjson::Value& inObj)
{
	Component::loadProperties(inObj);

	JsonHelper::getVector3(inObj, "objectMin", objectBox.min);
	JsonHelper::getVector3(inObj, "objectMax", objectBox.max);
	JsonHelper::getVector3(inObj, "worldMin", worldBox.min);
	JsonHelper::getVector3(inObj, "worldMax", worldBox.max);
	JsonHelper::getBool(inObj, "shouldRotate", shouldRotate);
}

void BoxComponent::saveProperties(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObj) const
{
	Component::saveProperties(alloc, inObj);

	JsonHelper::addVector3(alloc, inObj, "objectMin", objectBox.min);
	JsonHelper::addVector3(alloc, inObj, "objectMax", objectBox.max);
	JsonHelper::addVector3(alloc, inObj, "worldMin", worldBox.min);
	JsonHelper::addVector3(alloc, inObj, "worldMax", worldBox.max);
	JsonHelper::addBool(alloc, inObj, "shouldRotate", shouldRotate);
}
