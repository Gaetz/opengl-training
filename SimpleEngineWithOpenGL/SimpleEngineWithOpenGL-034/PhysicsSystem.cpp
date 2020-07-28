#include "PhysicsSystem.h"

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
