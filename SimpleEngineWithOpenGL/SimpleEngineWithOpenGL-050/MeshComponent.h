#pragma once
#include "Component.h"
class MeshComponent : public Component
{
public:
	MeshComponent(Actor* owner, bool isSkeletalP = false);
	virtual ~MeshComponent();

	bool getVisible() const { return isVisible; }
	bool getSkeletal() const { return isSkeletal; }
	void setVisible(bool isVisibleP);

	virtual void draw(class Shader& shader);
	virtual void setMesh(class Mesh& meshP);
	void setTextureIndex(size_t textureIndexP);
	ComponentType getType() const override { return ComponentType::Mesh; }
	void loadProperties(const rapidjson::Value& inObj) override;


protected:
	Mesh* mesh;
	size_t textureIndex;
	bool isVisible;
	bool isSkeletal;
};

