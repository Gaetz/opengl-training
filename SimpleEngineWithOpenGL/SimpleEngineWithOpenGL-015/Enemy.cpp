#include "Enemy.h"
#include "Game.h"
#include "ResourceManager.h"
#include "NavComponent.h"
#include "CircleCollisionComponent.h"
#include "Math.h"

Enemy::Enemy() : Actor(), circle(nullptr)
{
	getGame().getEnemies().emplace_back(this);

	SpriteComponent* sc = new SpriteComponent(*this, ResourceManager::getTexture("Airplane"));
	setPosition(getGame().getGrid().getStartTile().getPosition());
	NavComponent* nc = new NavComponent(*this);
	nc->setForwardSpeed(150.0f);
	nc->startPath(getGame().getGrid().getStartTile());
	circle = new CircleCollisionComponent(*this);
	circle->setRadius(25.0f);
}

Enemy::~Enemy()
{
	std::vector<Enemy*>& enemies = getGame().getEnemies();
	auto iter = std::find(begin(enemies), end(enemies), this);
	enemies.erase(iter);
}

void Enemy::updateActor(float dt)
{
	Actor::updateActor(dt);

	// Am I near the end tile?
	Vector2 dist = getPosition() - getGame().getGrid().getEndTile().getPosition();
	if (Maths::nearZero(dist.length(), 10.0f))
	{
		setState(ActorState::Dead);
	}
}
