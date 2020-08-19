#include "MoveComponent.h"
#include "Maths.h"
#include "Actor.h"
#include "Window.h"

MoveComponent::MoveComponent(Actor* ownerP, int updateOrderP)
	: Component(ownerP, updateOrderP), forwardSpeed(0.0f), angularSpeed(0.0f)
{

}

void MoveComponent::setForwardSpeed(float forwardSpeedP)
{
	forwardSpeed = forwardSpeedP;
}

void MoveComponent::setAngularSpeed(float angularSpeedP)
{
	angularSpeed = angularSpeedP;
}

void MoveComponent::update(float dt)
{
	if (!Maths::nearZero(angularSpeed))
	{
		float newRotation = owner.getRotation() + angularSpeed * dt;
		owner.setRotation(newRotation);
	}
	if (!Maths::nearZero(forwardSpeed))
	{
		Vector2 newPosition = owner.getPosition() + owner.getForward() * forwardSpeed * dt;

		// Screen wrapping (for asteroids)
		if (newPosition.x < 0) { newPosition.x = WINDOW_WIDTH; }
		else if (newPosition.x > WINDOW_WIDTH) { newPosition.x = 0; }
		if (newPosition.y < 0) { newPosition.y = WINDOW_HEIGHT; }
		else if (newPosition.y > WINDOW_HEIGHT) { newPosition.y = 0; }

		owner.setPosition(newPosition);
	}
}
