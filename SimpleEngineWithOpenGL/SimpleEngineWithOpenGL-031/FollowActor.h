#pragma once
#include "Actor.h"
class FollowActor : public Actor
{
public:
	FollowActor();

	void actorInput(const InputState& inputState) override;
	void setVisible(bool isVisibleP);

private:
	class MoveComponent* moveComponent;
	class FollowCameraComponent* cameraComponent;
	class MeshComponent* meshComponent;
};

