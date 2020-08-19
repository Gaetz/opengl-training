#include "Laser.h"
#include "SpriteComponent.h"
#include "Assets.h"
#include "MoveComponent.h"
#include "Game.h"
#include "Astroid.h"

Laser::Laser() : 
	Actor(), 
	deathTimer(1.0f), 
	collision(nullptr)
{
	new SpriteComponent(this, Assets::getTexture("Laser"));
	MoveComponent* mc = new MoveComponent(this);
	mc->setForwardSpeed(800.0f);
	collision = new CircleCollisionComponent(this);
	collision->setRadius(11.0f);
}

void Laser::updateActor(float dt)
{
	deathTimer -= dt;
	if (deathTimer <= 0.0f)
	{
		setState(Actor::ActorState::Dead);
	}
	else
	{
		auto astroids = getGame().getAstroids();
		for (auto astroid : astroids)
		{
			if (Intersect(*collision, astroid->getCollision()))
			{
				setState(ActorState::Dead);
				astroid->setState(ActorState::Dead);
				break;
			}
		}
	}
}
