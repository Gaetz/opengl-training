#pragma once

class Component
{
public:
	Component(class Actor* ownerP, int updateOrderP = 100);
	Component() = delete;
	virtual ~Component();

	virtual void update(float dt);
	inline int getUpdateOrder() const { return updateOrder; }

protected:
	class Actor* owner = nullptr;
	int updateOrder;		// Order of the component in the actor's updateComponent method

private:
	Component(const Component&) = delete;
	Component& operator=(const Component&) = delete;
};

