#pragma once
#include "Actor.h"
class Camera : public Actor
{
public:
	Camera();

	void updateActor(float deltaTime) override;
	void actorInput(const Uint8* keys) override;
private:
	class MoveComponent* moveComponent;
};
