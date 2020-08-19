#pragma once
#include "Component.h"
#include "Vector3.h"
class PointLightComponent : public Component
{
public:
	PointLightComponent(class Actor* owner);
	virtual ~PointLightComponent();

	void draw(class Shader& shader, class Mesh& mesh);

	Vector3 diffuseColor;
	float innerRadius;
	float outerRadius;
};

