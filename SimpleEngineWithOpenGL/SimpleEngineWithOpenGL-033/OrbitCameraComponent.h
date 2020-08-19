#pragma once
#include "CameraComponent.h"
class OrbitCameraComponent : public CameraComponent
{
public:
	OrbitCameraComponent(class Actor* owner);

	void update(float dt) override;

	float getPitchSpeed() const { return pitchSpeed; }
	float getYawSpeed() const { return yawSpeed; }

	void setPitchSpeed(float pitchSpeedP);
	void setYawSpeed(float yawSpeedP);


private:
	// Offset from target
	Vector3 offset;
	// Up vector of camera
	Vector3 up;

	float pitchSpeed;
	float yawSpeed;
};

