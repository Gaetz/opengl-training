#pragma once
#include "Actor.h"


class Tower : public Actor
{
public:
	Tower();
	void updateActor(float dt) override;


private:
	class MoveComponent* move;
	float nextAttackTimer;
	const float ATTACK_TIME = 2.5f;
	const float ATTACK_RANGE = 100.0f;
};

