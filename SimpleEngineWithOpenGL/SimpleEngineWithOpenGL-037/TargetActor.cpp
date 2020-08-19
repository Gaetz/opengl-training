#include "TargetActor.h"
#include "MeshComponent.h"
#include "BoxComponent.h"
#include "Mesh.h"
#include "Assets.h"

TargetActor::TargetActor()
{
	setRotation(Quaternion(Vector3::unitZ, Maths::pi));
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Target"));
	// Add collision box
	BoxComponent* bc = new BoxComponent(this);
	bc->setObjectBox(Assets::getMesh("Mesh_Target").getBox());
}
