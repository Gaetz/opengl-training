#include "OrbitActor.h"
#include "MeshComponent.h"
#include "OrbitCameraComponent.h"
#include "Assets.h"
#include "InputSystem.h"

OrbitActor::OrbitActor() : Actor(), cameraComponent(nullptr), meshComponent(nullptr)
{
	meshComponent = new MeshComponent(this);
	meshComponent->setMesh(Assets::getMesh("Mesh_RacingCar"));
	setPosition(Vector3(0.0f, 0.0f, -100.0f));
	cameraComponent = new OrbitCameraComponent(this);
}

void OrbitActor::actorInput(const InputState& inputState)
{
	Vector2 mousePosition = inputState.mouse.getPosition();
	float x = mousePosition.x;
	float y = mousePosition.y;
	if (inputState.mouse.getButtonState(3) == ButtonState::Held)
	{
		const float maxMouseSpeed = 500.0f;
		const float maxOrbitSpeed = Maths::pi * 8;

		float yawSpeed = 0.0f;
		if (!Maths::nearZero(x))
		{
			yawSpeed = x / maxMouseSpeed;
			yawSpeed *= maxOrbitSpeed;
		}
		cameraComponent->setYawSpeed(yawSpeed);

		float pitchSpeed = 0.0f;
		if (!Maths::nearZero(y))
		{
			pitchSpeed = y / maxMouseSpeed;
			pitchSpeed *= maxOrbitSpeed;
		}
		cameraComponent->setPitchSpeed(pitchSpeed);
	}
}

void OrbitActor::setVisible(bool visible)
{
	meshComponent->setVisible(visible);
}
