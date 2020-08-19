#include "FollowActor.h"
#include "MoveComponent.h"
#include "FollowCameraComponent.h"
#include "SkeletalMeshComponent.h"
#include "Assets.h"
#include "InputSystem.h"
#include "MirrorCameraComponent.h"
#include "Game.h"

FollowActor::FollowActor() :
	Actor(),
	moveComponent(nullptr),
	cameraComponent(nullptr),
	meshComponent(nullptr)
{
	meshComponent = new SkeletalMeshComponent(this);
	meshComponent->setMesh(Assets::getMesh("Mesh_CatWarrior"));
	meshComponent->setSkeleton(Assets::getSkeleton("Skel_CatWarrior"));
	meshComponent->playAnimation(&Assets::getAnimation("CatActionIdle"));

	setPosition(Vector3(0.0f, 0.0f, -100.0f));

	moveComponent = new MoveComponent(this);
	cameraComponent = new FollowCameraComponent(this);
	cameraComponent->snapToIdeal();

	MirrorCameraComponent* mirror = new MirrorCameraComponent(this);
	mirror->snapToIdeal();

	Game::instance().setPlayer(this);
}

void FollowActor::actorInput(const InputState& inputState)
{
	float forwardSpeed = 0.0f;
	float angularSpeed = 0.0f;
	// wasd movement
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_W))
	{
		forwardSpeed += 800.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_S))
	{
		forwardSpeed -= 800.0f;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_A))
	{
		angularSpeed -= Maths::pi;
	}
	if (inputState.keyboard.getKeyValue(SDL_SCANCODE_D))
	{
		angularSpeed += Maths::pi;
	}

	// Did we just start moving?
	if (!isMoving && !Maths::nearZero(forwardSpeed))
	{
		isMoving = true;
		meshComponent->playAnimation(&Assets::getAnimation("CatRunSprint"), 1.25f);
	}
	// Or did we just stop moving?
	else if (isMoving && Maths::nearZero(forwardSpeed))
	{
		isMoving = false;
		meshComponent->playAnimation(&Assets::getAnimation("CatActionIdle"));
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
