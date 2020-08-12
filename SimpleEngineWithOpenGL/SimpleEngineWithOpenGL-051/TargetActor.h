#pragma once
#include "Actor.h"

class TargetActor : public Actor
{
public:
	TargetActor();
	ActorType getType() const override { return ActorType::TargetActor; }
};

