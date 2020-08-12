#pragma once
#include <vector>
#include "Vector2.h"
#include <SDL_stdinc.h>
#include "Matrix4.h"
#include <rapidjson/document.h>
#include "Component.h"

using std::vector;

class Game;

enum class ActorType
{
	Actor = 0,
	BallActor,
	FollowActor,
	PlaneActor,
	TargetActor,

	NB_ACTOR_TYPES
};

class Actor
{
public:

	static const char* typeNames[static_cast<int>(ActorType::NB_ACTOR_TYPES)];

	enum class ActorState
	{
		Active, Paused, Dead
	};

	Actor();
	virtual ~Actor();
	Actor(const Actor&) = delete;
	Actor& operator=(const Actor&) = delete;

	Game& getGame() const { return game; }
	const ActorState getState() const { return state; }
	const Vector3 getPosition() const { return position; }
	const float getScale() const { return scale; }
	const Quaternion getRotation() const { return rotation; }
	const Matrix4& getWorldTransform() const { return worldTransform;  }

	void setPosition(Vector3 positionP);
	void setScale(float scaleP);
	void setRotation(Quaternion rotationP);
	void setState(ActorState stateP);

	void setAngle(const Vector3& axis, float angle);
	void rotate(const Vector3& axis, float angle);
	Vector3 getForward() const;
	Vector3 getRight() const;
	void computeWorldTransform();
	void rotateToNewForward(const Vector3& newForward);

	void processInput(const struct InputState& inputState);
	virtual void actorInput(const struct InputState& inputState);
	void update(float dt);
	void updateComponents(float dt);
	virtual void updateActor(float dt);
	void addComponent(Component* component);
	void removeComponent(Component* component);

	virtual ActorType getType() const { return ActorType::Actor; }
	virtual void loadProperties(const rapidjson::Value& inObj);
	virtual void saveProperties(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObj) const;
	const vector<Component*>& getComponents() const { return components; }

	Component* getComponentOfType(ComponentType type)
	{
		Component* comp = nullptr;
		for (Component* c : components)
		{
			if (c->getType() == type)
			{
				comp = c;
				break;
			}
		}
		return comp;
	}

	// Create an actor with specified properties
	template <typename T>
	static Actor* Create(const rapidjson::Value& inObj)
	{
		// Dynamically allocate actor of type T
		T* t = new T();
		// Call LoadProperties on new actor
		t->loadProperties(inObj);
		return t;
	}

private:
	Game& game;
	ActorState state;
	Vector3 position;
	float scale;
	Quaternion rotation;
	Matrix4 worldTransform;
	bool mustRecomputeWorldTransform;

	vector<Component*> components;
};

