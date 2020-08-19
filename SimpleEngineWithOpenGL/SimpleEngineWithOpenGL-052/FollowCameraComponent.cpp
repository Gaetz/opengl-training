#include "FollowCameraComponent.h"
#include "Actor.h"
#include "LevelLoader.h"

FollowCameraComponent::FollowCameraComponent(Actor* ownerP):
	CameraComponent(ownerP),
	horizontalDistance(FOLLOW_HORIZONTAL_DISTANCE),
	verticalDistance(FOLLOW_VERTICAL_DISTANCE),
	targetDistance(FOLLOW_TARGET_DISTANCE),
	springConstant(FOLLOW_SPRING_CONSTANT)
{
}

void FollowCameraComponent::update(float dt)
{
	CameraComponent::update(dt);

	float dampening = 2.0f * Maths::sqrt(springConstant);
	Vector3 idealPosition = computeCameraPosition();
	Vector3 diff = actualPosition - idealPosition;
	Vector3 accel = -springConstant * diff - dampening * velocity;
	velocity += accel * dt;
	actualPosition += velocity * dt;

	Vector3 target = owner.getPosition() + owner.getForward() * targetDistance;
	Matrix4 view = Matrix4::createLookAt(actualPosition, target, Vector3::unitZ);
	setViewMatrix(view);
}

void FollowCameraComponent::snapToIdeal()
{
	actualPosition = computeCameraPosition();
	velocity = Vector3::zero;
	Vector3 target = owner.getPosition() + owner.getForward() * targetDistance;
	Matrix4 view = Matrix4::createLookAt(actualPosition, target, Vector3::unitZ);
	setViewMatrix(view);
}

void FollowCameraComponent::setHorizontalDistance(float distance)
{
	horizontalDistance = distance;
}

void FollowCameraComponent::setVerticalDistance(float distance)
{
	verticalDistance = distance;
}

void FollowCameraComponent::setTargetDistance(float distance)
{
	targetDistance = distance;
}

void FollowCameraComponent::setSpringConstant(float springConstantP)
{
	springConstant = springConstantP;
}

void FollowCameraComponent::loadProperties(const rapidjson::Value& inObj)
{
	CameraComponent::loadProperties(inObj);

	JsonHelper::getVector3(inObj, "actualPos", actualPosition);
	JsonHelper::getVector3(inObj, "velocity", velocity);
	JsonHelper::getFloat(inObj, "horzDist", horizontalDistance);
	JsonHelper::getFloat(inObj, "vertDist", verticalDistance);
	JsonHelper::getFloat(inObj, "targetDist", targetDistance);
	JsonHelper::getFloat(inObj, "springConstant", springConstant);
}

void FollowCameraComponent::saveProperties(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObj) const
{
	CameraComponent::saveProperties(alloc, inObj);

	JsonHelper::addVector3(alloc, inObj, "actualPos", actualPosition);
	JsonHelper::addVector3(alloc, inObj, "velocity", velocity);
	JsonHelper::addFloat(alloc, inObj, "horzDist", horizontalDistance);
	JsonHelper::addFloat(alloc, inObj, "vertDist", verticalDistance);
	JsonHelper::addFloat(alloc, inObj, "targetDist", targetDistance);
	JsonHelper::addFloat(alloc, inObj, "springConstant", springConstant);
}

Vector3 FollowCameraComponent::computeCameraPosition() const
{
	Vector3 cameraPosition = owner.getPosition();
	cameraPosition -= owner.getForward() * horizontalDistance;
	cameraPosition += Vector3::unitZ * verticalDistance;
	return cameraPosition;
}
