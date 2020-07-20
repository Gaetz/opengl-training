#pragma once
#include "Actor.h"
#include <SDL_stdinc.h>

class Ship : public Actor
{
public:
	Ship();

	void actorInput(const struct InputState& inputState) override;
	void updateActor(float dt) override;


private:
	float laserCooldown;
	Vector2 velocityDir;
	Vector2 rotationDir;
	float speed;
};

