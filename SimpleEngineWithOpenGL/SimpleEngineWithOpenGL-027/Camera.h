#pragma once
#include "Actor.h"
#include "SoundEvent.h"

class Camera : public Actor
{
public:
	Camera();

	void updateActor(float deltaTime) override;
	void actorInput(const struct InputState& inputState) override;

	void setFootstepSurface(float value);


private:
	class MoveComponent* moveComponent;
	class AudioComponent* audioComponent;

	SoundEvent footstep;
	float lastFootstep;
};
