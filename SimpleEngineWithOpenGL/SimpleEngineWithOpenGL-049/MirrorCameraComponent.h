#pragma once
#include "CameraComponent.h"
class MirrorCameraComponent : public CameraComponent
{
public:
	MirrorCameraComponent(class Actor* owner);

	void setHorizontalDist(float dist) { horizontalDist = dist; }
	void setVerticalDist(float dist) { verticalDist = dist; }
	void setTargetDist(float dist) { targetDist = dist; }

	void update(float dt) override;
	void snapToIdeal();


private:
	Vector3 computeCameraPosition() const;

	float horizontalDist;
	float verticalDist;
	float targetDist;
};

