#include "MirrorCameraComponent.h"
#include "Actor.h"
#include "Game.h"
#include "LevelLoader.h"

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

void MirrorCameraComponent::loadProperties(const rapidjson::Value& inObj)
{
	CameraComponent::loadProperties(inObj);

	JsonHelper::getFloat(inObj, "horzDist", horizontalDist);
	JsonHelper::getFloat(inObj, "vertDist", verticalDist);
	JsonHelper::getFloat(inObj, "targetDist", targetDist);
}

void MirrorCameraComponent::saveProperties(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObj) const
{
	CameraComponent::saveProperties(alloc, inObj);

	JsonHelper::addFloat(alloc, inObj, "horzDist", horizontalDist);
	JsonHelper::addFloat(alloc, inObj, "vertDist", verticalDist);
	JsonHelper::addFloat(alloc, inObj, "targetDist", targetDist);
}

Vector3 MirrorCameraComponent::computeCameraPosition() const
{
	Vector3 cameraPos = owner.getPosition();
	cameraPos += owner.getForward() * horizontalDist;
	cameraPos += Vector3::unitZ * verticalDist;
	return cameraPos;
}
