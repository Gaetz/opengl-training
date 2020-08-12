#pragma once
#include "Actor.h"
class BallActor : public Actor
{
public:
	BallActor();

	void updateActor(float dt) override;
	void setPlayer(Actor* player);
	void hitTarget();

	void loadProperties(const rapidjson::Value& inObj) override;
	void saveProperties(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObj) const override;
	ActorType getType() const override { return ActorType::BallActor; }

private:
	class AudioComponent* audio;
	class BallMoveComponent* ballMove;
	float lifetimeSpan;
};

