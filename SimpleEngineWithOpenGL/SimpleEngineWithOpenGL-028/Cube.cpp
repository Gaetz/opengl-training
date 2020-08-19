#include "Cube.h"
#include "MeshComponent.h"
#include "Assets.h"

Cube::Cube()
{
	MeshComponent* mc = new MeshComponent(this);
	mc->setMesh(Assets::getMesh("Mesh_Cube"));
}
