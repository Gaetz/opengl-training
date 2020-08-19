#include "FollowActor.h"
#include "MoveComponent.h"
#include "FollowCameraComponent.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "InputSystem.h"

FollowActor::FollowActor() :
	Actor(),
	moveComponent(nullptr),
	cameraComponent(nullptr),
	meshComponent(nullptr)
{
	meshComponent = new MeshComponent(this);
	meshComponent->setMesh(Assets::getMesh("Mesh_RacingCar"));
	setPosition(Vector3(0.0f, 0.0f, -100.0f));

	moveComponent = new MoveComponent(this);
	cameraComponent = new FollowCameraComponent(this);
	cameraComponent->snapToIdeal();
}

void FollowActor::actorInput(const InputState& inputState)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;
	// wasd movement
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_W))
	{
		forwardSpeed += 400.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_S))
	{
		forwardSpeed -= 400.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_A))
	{
		angularSpeed -= Maths::pi;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_D))
	{
		angularSpeed += Maths::pi;
	}

	moveComponent->setForwardSpeed(forwardSpeed);
	moveComponent->setAngularSpeed(angularSpeed);

	// Adjust horizontal distance of camera based on speed
	if (!Maths::nearZero(forwardSpeed))
	{
		cameraComponent->setHorizontalDistance(500.0f);
	}
	else
	{
		cameraComponent->setHorizontalDistance(350.0f);
	}
}

void FollowActor::setVisible(bool isVisibleP)
{
	meshComponent->setVisible(isVisibleP);
}
