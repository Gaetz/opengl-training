#pragma once
#include <vector>
#include "Vector2.h"
#include <SDL_stdinc.h>
#include "Matrix4.h"
using std::vector;

class Game;
class Component;

class Actor
{
public:

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

	Vector3 getForward() const;
	void computeWorldTransform();

	void processInput(const Uint8* keyState);
	virtual void actorInput(const Uint8* keyState);
	void update(float dt);
	void updateComponents(float dt);
	virtual void updateActor(float dt);
	void addComponent(Component* component);
	void removeComponent(Component* component);

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

