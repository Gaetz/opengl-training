#pragma once
#include "Actor.h"
class PlaneActor : public Actor
{
public:
	PlaneActor();
	~PlaneActor();
	class BoxComponent* getBox() { return box; }
	ActorType getType() const override { return ActorType::PlaneActor; }


private:
	class BoxComponent* box;
};

