#include "PlaneActor.h"
#include "MeshComponent.h"
#include "Assets.h"

PlaneActor::PlaneActor() : Actor()
{
	setScale(10.0f);
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Plane"));
}
