#pragma once
#include <vector>
#include "Vector2.h"
#include "Component.h"
using std::vector;

class Actor
{
public:

	enum class ActorState
	{
		Active, Paused, Dead
	};

	Actor(class Game* gameP);
	Actor() = delete;
	virtual ~Actor();

	void update(float dt);
	void updateComponents(float dt);
	virtual void updateActor(float dt);
	void addComponent(Component* component);
	void removeComponent(Component* component);

	inline const ActorState& getState() { return state; }

private:
	Game* game = nullptr;
	ActorState state;
	Vector2 position;
	float scale;
	float rotation;	// Rotation in radians

	vector<Component*> components;

	Actor(const Actor&) = delete;
	Actor& operator=(const Actor&) = delete;
};

