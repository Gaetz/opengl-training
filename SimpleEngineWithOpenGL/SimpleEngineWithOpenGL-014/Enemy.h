#pragma once
#include "Actor.h"

class Enemy : public Actor
{
public:
	Enemy();
	virtual ~Enemy();
	void updateActor(float dt) override;
	class CircleCollisionComponent& GetCircle() { return *circle; }


private:
	class CircleCollisionComponent* circle;
};

