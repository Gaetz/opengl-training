#include "Bullet.h"
#include "SpriteComponent.h"
#include "MoveComponent.h"
#include "CircleCollisionComponent.h"
#include "Game.h"
#include "Enemy.h"
#include "Assets.h"

Bullet::Bullet()
{
	SpriteComponent* sc = new SpriteComponent(this, Assets::getTexture("Projectile"));
	MoveComponent* mc = new MoveComponent(this);
	mc->setForwardSpeed(400.0f);
	circle = new CircleCollisionComponent(this);
	circle->setRadius(5.0f);
	lifetime = 1.0f;
}

void Bullet::updateActor(float dt)
{
	Actor::updateActor(dt);

	for (Enemy* e : getGame().getEnemies())
	{
		if (Intersect(*circle, e->getCircle()))
		{
			// Both die on collision
			e->setState(ActorState::Dead);
			setState(ActorState::Dead);
			break;
		}
	}

	lifetime -= dt;
	if (lifetime <= 0.0f)
	{
		setState(ActorState::Dead);
	}
}
