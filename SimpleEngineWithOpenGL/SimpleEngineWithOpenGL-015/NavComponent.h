#pragma once
#include "MoveComponent.h"
#include "Vector2.h"

class NavComponent : public MoveComponent
{
public:
	NavComponent(class Actor* owner, int updateOrder = 10);
	NavComponent() = delete;
	NavComponent(const NavComponent&) = delete;
	NavComponent& operator=(const NavComponent&) = delete;

	void update(float dt) override;
	void startPath(const class Tile& start);
	void turnTo(const Vector2& targetPosition);


private:
	const class Tile* nextNode;
};

