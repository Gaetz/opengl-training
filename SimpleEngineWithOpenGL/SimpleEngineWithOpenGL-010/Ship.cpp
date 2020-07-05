#include "Ship.h"
#include "SpriteComponent.h"
#include "ResourceManager.h"
#include "InputComponent.h"
#include "Math.h"

Ship::Ship() : Actor()
{
	SpriteComponent* sc = new SpriteComponent(*this, ResourceManager::getTexture("Ship"));
	InputComponent* ic = new InputComponent(*this);
	ic->setMaxForwardSpeed(300.0f);
	ic->setMaxAngularSpeed(Maths::twoPi);
}

