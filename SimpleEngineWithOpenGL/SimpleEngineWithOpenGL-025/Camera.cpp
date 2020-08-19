#include "Camera.h"
#include "MoveComponent.h"
#include "Game.h"
#include "AudioComponent.h"

Camera::Camera() : Actor(), moveComponent(nullptr), audioComponent(nullptr), lastFootstep(0.0f)
{
	moveComponent = new MoveComponent(this);
	audioComponent = new AudioComponent(this);
	footstep = audioComponent->playEvent("event:/Footstep");
	footstep.setPaused(true);
}

void Camera::updateActor(float deltaTime)
{
	Actor::updateActor(deltaTime);

	// Play the footstep if we're moving and haven't recently
	lastFootstep -= deltaTime;
	if (!Maths::nearZero(moveComponent->getForwardSpeed()) && lastFootstep <= 0.0f)
	{
		footstep.setPaused(false);
		footstep.restart();
		lastFootstep = 0.5f;
	}

	// Compute new camera from this actor
	Vector3 cameraPos = getPosition();
	Vector3 target = getPosition() + getForward() * 100.0f;
	Vector3 up = Vector3::unitZ;

	Matrix4 view = Matrix4::createLookAt(cameraPos, target, up);
	getGame().getRenderer().setViewMatrix(view);
	getGame().getAudioSystem().setListener(view);
}

void Camera::actorInput(const Uint8* keys)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;
	// wasd movement
	if (keys[SDL_SCANCODE_W])
	{
		forwardSpeed += 300.0f;
	}
	if (keys[SDL_SCANCODE_S])
	{
		forwardSpeed -= 300.0f;
	}
	if (keys[SDL_SCANCODE_A])
	{
		angularSpeed -= Maths::twoPi;
	}
	if (keys[SDL_SCANCODE_D])
	{
		angularSpeed += Maths::twoPi;
	}

	moveComponent->setForwardSpeed(forwardSpeed);
	moveComponent->setAngularSpeed(angularSpeed);
}

void Camera::setFootstepSurface(float value)
{
	// Pause here because the way I setup the parameter in FMOD
	// changing it will play a footstep
	footstep.setPaused(true);
	footstep.setParameter("Surface", value);
}