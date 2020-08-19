#include "NavComponent.h"
#include "Actor.h"
#include "Tile.h"
#include "Maths.h"

NavComponent::NavComponent(Actor* owner, int updateOrder):
	MoveComponent(owner, updateOrder),
	nextNode(nullptr)
{

}

void NavComponent::update(float dt)
{
	if (nextNode)
	{
		Vector2 dist = owner.getPosition() - nextNode->getPosition();
		if (Maths::nearZero(dist.length(), 2.0f))
		{
			nextNode = nextNode->getParent();
			turnTo(nextNode->getPosition());
		}
	}
	MoveComponent::update(dt);
}

void NavComponent::startPath(const Tile& start)
{
	nextNode = start.getParent();
	turnTo(nextNode->getPosition());
}

void NavComponent::turnTo(const Vector2& targetPosition)
{
	Vector2 dir = targetPosition - owner.getPosition();
	float angle = Maths::atan2(-dir.y, dir.x);
	owner.setRotation(angle);
}
