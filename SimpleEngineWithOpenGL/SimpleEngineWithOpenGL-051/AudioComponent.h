#pragma once
#include "Component.h"
#include "SoundEvent.h"
#include <vector>
#include <string>

class AudioComponent : public Component
{
public:
	AudioComponent(class Actor* owner, int updateOrder = 200);
	~AudioComponent();

	void update(float dt) override;
	void onUpdateWorldTransform() override;

	SoundEvent playEvent(const std::string& name);
	void stopAllEvents();

	ComponentType getType() const override { return ComponentType::Audio; }

private:
	std::vector<SoundEvent> events2D;
	std::vector<SoundEvent> events3D;
};

