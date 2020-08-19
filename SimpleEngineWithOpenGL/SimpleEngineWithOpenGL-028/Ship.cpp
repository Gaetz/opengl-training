#include "Ship.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "InputComponent.h"
#include "Maths.h"
#include "Laser.h"
#include "InputSystem.h"

Ship::Ship() : Actor(), laserCooldown(0.0f), speed(400.0f)
{
	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Ship"));
}

void Ship::actorInput(const InputState& inputState)
{
	if (inputState.controller.getRightTrigger() > 0.25f && laserCooldown <= 0.0f)
	{
		Laser* laser = new Laser();
		laser->setPosition(getPosition());
		laser->setRotation(getRotation());
		laserCooldown = 0.2f;
	}

	if (inputState.controller.getIsConnected())
	{
		velocityDir = inputState.controller.getLeftStick();
		if (!Maths::nearZero(inputState.controller.getRightStick().length()))
		{
			rotationDir = inputState.controller.getRightStick();
		}
	}
}

void Ship::updateActor(float dt)
{
	laserCooldown -= dt;

	Vector2 position = Vector2(getPosition().x, getPosition().y);
	position += velocityDir * speed * dt;
	setPosition(Vector3(position.x, position.y, 0.0f));

	float angle = Maths::atan2(rotationDir.y, rotationDir.x);
	setAngle(Vector3::unitZ, angle);
}

