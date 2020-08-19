#pragma once
#include <SDL_stdinc.h>
#include <rapidjson/document.h>

class Actor;

enum class ComponentType
{
	Component = 0,
	Audio,
	BallMove,
	Box,
	Camera,
	FollowCamera,
	Mesh,
	MirrorCamera,
	Move,
	PointLight,
	SkeletalMesh,
	Sprite,
	Target,

	NB_COMPONENT_TYPES
};

class Component
{
public:
	Component(Actor* ownerP, int updateOrderP = 100);
	Component() = delete;
	virtual ~Component();
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;

	int getUpdateOrder() const { return updateOrder; }
	class Actor& getOwner() { return owner; }

	virtual void processInput(const struct InputState& inputState);
	virtual void update(float dt);
	virtual void onUpdateWorldTransform() {}

	virtual ComponentType getType() const = 0;
	virtual void loadProperties(const rapidjson::Value& inObj);

	// Create a component with specified properties
	template <typename T>
	static Component* Create(class Actor* actor, const rapidjson::Value& inObj)
	{
		// Dynamically allocate component of type T
		T* t = new T(actor);
		// Call loadProperties on new component
		t->loadProperties(inObj);
		return t;
	}

protected:
	Actor& owner;
	int updateOrder;		// Order of the component in the actor's updateComponent method
};

