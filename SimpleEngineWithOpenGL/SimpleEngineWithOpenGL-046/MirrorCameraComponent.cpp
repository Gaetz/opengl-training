#include "MirrorCameraComponent.h"
#include "Actor.h"
#include "Game.h"

MirrorCameraComponent::MirrorCameraComponent(Actor* owner):
	CameraComponent(owner),
	horizontalDist(150.0f),
	verticalDist(200.0f),
	targetDist(400.0f)
{
}

void MirrorCameraComponent::update(float dt)
{
	CameraComponent::update(dt);
	snapToIdeal();
}

void MirrorCameraComponent::snapToIdeal()
{
	Vector3 idealPos = computeCameraPosition();
	Vector3 target = owner.getPosition() - owner.getForward() * targetDist;
	// Use actual position here, not ideal
	Matrix4 view = Matrix4::createLookAt(idealPos, target, Vector3::unitZ);
	Game::instance().getRenderer().setMirrorView(view);
}

Vector3 MirrorCameraComponent::computeCameraPosition() const
{
	Vector3 cameraPos = owner.getPosition();
	cameraPos += owner.getForward() * horizontalDist;
	cameraPos += Vector3::unitZ * verticalDist;
	return cameraPos;
}
