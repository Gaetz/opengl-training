#pragma once
#include "Actor.h"
class FollowActor : public Actor
{
public:
	FollowActor();

	void actorInput(const InputState& inputState) override;
	void setVisible(bool isVisibleP);

	void loadProperties(const rapidjson::Value& inObj) override;
	void saveProperties(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObj) const override;
	ActorType getType() const override { return ActorType::FollowActor; }

private:
	class MoveComponent* moveComponent;
	class FollowCameraComponent* cameraComponent;
	class SkeletalMeshComponent* meshComponent;
	bool isMoving;
};

