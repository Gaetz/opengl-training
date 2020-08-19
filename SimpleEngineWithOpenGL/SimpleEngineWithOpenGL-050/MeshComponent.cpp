#include "MeshComponent.h"
#include "Actor.h"
#include "Game.h"
#include "Mesh.h"
#include "LevelLoader.h"
#include "Assets.h"

MeshComponent::MeshComponent(Actor* owner, bool isSkeletalP) : Component(owner), mesh(nullptr), textureIndex(0), isVisible(true), isSkeletal(isSkeletalP)
{
	owner->getGame().getRenderer().addMesh(this);
}

MeshComponent::~MeshComponent()
{
	owner.getGame().getRenderer().removeMesh(this);
}

void MeshComponent::setVisible(bool isVisibleP)
{
	isVisible = isVisibleP;
}

void MeshComponent::draw(Shader& shader)
{
	if (mesh)
	{
		Matrix4 wt = owner.getWorldTransform();
		shader.setMatrix4("uWorldTransform", wt);
		shader.setFloat("uSpecPower", mesh->getSpecularPower());
		Texture* t = mesh->getTexture(textureIndex);
		if (t)
		{
			t->setActive();
		}
		VertexArray* va = mesh->getVertexArray();
		va->setActive();
		glDrawElements(GL_TRIANGLES, va->getNbIndices(), GL_UNSIGNED_INT, nullptr);
	}
}

void MeshComponent::setMesh(Mesh& meshP)
{
	mesh = &meshP;
}

void MeshComponent::setTextureIndex(size_t textureIndexP)
{
	textureIndex = textureIndexP;
}

void MeshComponent::loadProperties(const rapidjson::Value& inObj)
{
	Component::loadProperties(inObj);

	std::string meshFile;
	if (JsonHelper::getString(inObj, "meshFile", meshFile))
	{
		setMesh(Assets::getMesh(meshFile));
	}

	int idx;
	if (JsonHelper::getInt(inObj, "textureIndex", idx))
	{
		textureIndex = static_cast<size_t>(idx);
	}

	JsonHelper::getBool(inObj, "visible", isVisible);
	JsonHelper::getBool(inObj, "isSkeletal", isSkeletal);
}
