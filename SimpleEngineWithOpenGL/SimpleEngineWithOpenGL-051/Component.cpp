#include "Component.h"
#include "Actor.h"
#include "InputSystem.h"
#include "LevelLoader.h"

const char* Component::typeNames[static_cast<int>(ComponentType::NB_COMPONENT_TYPES)] = {
	"Component",
	"Audio",
	"BallMove",
	"Box",
	"Camera",
	"Follow",
	"Mesh",
	"MirrorCamera",
	"MoveComponent",
	"PointLight",
	"SkeletalMesh",
	"Sprite",
	"Target"
};

Component::Component(Actor* ownerP, int updateOrderP):
	owner(*ownerP),
	updateOrder(updateOrderP)
{
	owner.addComponent(this);
}

Component::~Component()
{
	owner.removeComponent(this);
}

void Component::processInput(const InputState& inputState)
{
}

void Component::update(float dt)
{
}

void Component::loadProperties(const rapidjson::Value& inObj)
{
	JsonHelper::getInt(inObj, "updateOrder", updateOrder);
}

void Component::saveProperties(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObj) const
{
	JsonHelper::addInt(alloc, inObj, "updateOrder", updateOrder);
}
