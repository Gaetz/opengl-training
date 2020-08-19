#pragma once
#include "Component.h"
class TargetComponent : public Component
{
public:
	TargetComponent(class Actor* owner);
	~TargetComponent();

	ComponentType getType() const override { return ComponentType::Target; }

};

