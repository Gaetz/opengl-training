#include "PhysicsSystem.h"
#include "Collisions.h"
#include "BoxComponent.h"

PhysicsSystem::PhysicsSystem()
{
}

void PhysicsSystem::addBox(BoxComponent* box)
{
	boxes.emplace_back(box);
}

void PhysicsSystem::removeBox(BoxComponent* box)
{
	auto iter = std::find(begin(boxes), end(boxes), box);
	if (iter != end(boxes))
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, boxes.end() - 1);
		boxes.pop_back();
	}
}

bool PhysicsSystem::segmentCast(const LineSegment& l, CollisionInfo& outColl)
{
	bool collided = false;
	// Initialize closestT to infinity, so first
	// intersection will always update closestT
	float closestT = Maths::infinity;
	Vector3 norm;
	// Test against all boxes
	for (auto box : boxes)
	{
		float t;
		// Does the segment intersect with the box?
		if (Collisions::intersect(l, box->getWorldBox(), t, norm))
		{
			// Is this closer than previous intersection?
			if (t < closestT)
			{
				outColl.point = l.pointOnSegment(t);
				outColl.normal = norm;
				outColl.box = box;
				outColl.actor = &box->getOwner();
				collided = true;
			}
		}
	}
	return collided;
}
