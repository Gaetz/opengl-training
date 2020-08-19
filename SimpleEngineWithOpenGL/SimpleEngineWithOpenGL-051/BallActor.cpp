#include "BallActor.h"
#include "MeshComponent.h"
#include "Assets.h"
#include "AudioComponent.h"
#include "BallMoveComponent.h"
#include "LevelLoader.h"

BallActor::BallActor() : Actor(), lifetimeSpan(2.0f), audio(nullptr), ballMove(nullptr)
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Sphere"));
	audio = new AudioComponent(this);
	ballMove = new BallMoveComponent(this);
	ballMove->setForwardSpeed(1500.0f);
}

void BallActor::updateActor(float dt)
{
	Actor::updateActor(dt);

	lifetimeSpan -= dt;
	if (lifetimeSpan < 0.0f)
	{
		setState(ActorState::Dead);
	}
}

void BallActor::setPlayer(Actor* player)
{
	ballMove->setPlayer(player);
}

void BallActor::hitTarget()
{
	audio->playEvent("event:/Ding");
}

void BallActor::loadProperties(const rapidjson::Value& inObj)
{
	Actor::loadProperties(inObj);
	JsonHelper::getFloat(inObj, "lifespan", lifetimeSpan);
}

void BallActor::saveProperties(rapidjson::Document::AllocatorType& alloc, rapidjson::Value& inObj) const
{
	Actor::saveProperties(alloc, inObj);
	JsonHelper::addFloat(alloc, inObj, "lifespan", lifetimeSpan);
}
