#pragma once
#include "Actor.h"
class Bullet : public Actor
{
public:
	Bullet();
	void updateActor(float dt) override;


private:
	class CircleCollisionComponent* circle;
	float lifetime;
};

