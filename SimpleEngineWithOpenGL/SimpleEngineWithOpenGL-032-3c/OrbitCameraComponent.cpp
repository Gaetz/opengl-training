#include "OrbitCameraComponent.h"
#include "Actor.h"

OrbitCameraComponent::OrbitCameraComponent(Actor* ownerP):
	CameraComponent(ownerP),
	offset(-400.0f, 0.0f, 0.0f),
	up(Vector3::unitZ),
	pitchSpeed(0.0f),
	yawSpeed(0.0f)
{
}

void OrbitCameraComponent::update(float dt)
{
	CameraComponent::update(dt);

	Quaternion yaw { Vector3::unitZ, yawSpeed * dt };
	offset = Vector3::transform(offset, yaw);
	up = Vector3::transform(up, yaw);

	// Compute camera forward/right from these vectors
	// Forward owner.position - (owner.position + offset) = -offset
	Vector3 forward = -1.0f * offset;
	forward.normalize();
	Vector3 right = Vector3::cross(up, forward);
	right.normalize();

	Quaternion pitch { right, pitchSpeed * dt };
	offset = Vector3::transform(offset, pitch);
	up = Vector3::transform(up, pitch);

	Vector3 target = owner.getPosition();
	Vector3 cameraPosition = target + offset;
	Matrix4 view = Matrix4::createLookAt(cameraPosition, target, up);
	setViewMatrix(view);
}

void OrbitCameraComponent::setPitchSpeed(float pitchSpeedP)
{
	pitchSpeed = pitchSpeedP;
}

void OrbitCameraComponent::setYawSpeed(float yawSpeedP)
{
	yawSpeed = yawSpeedP;
}
