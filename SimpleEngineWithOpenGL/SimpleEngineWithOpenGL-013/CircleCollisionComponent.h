#pragma once
#include "Component.h"
#include "Vector2.h"

class CircleCollisionComponent : public Component
{
public:
	CircleCollisionComponent(Actor& owner);

	float getRadius() const;
	void setRadius(float radiusP);

	const Vector2& getCenter() const;

private:
	float radius;
};

bool Intersect(const CircleCollisionComponent& a, const CircleCollisionComponent& b);
