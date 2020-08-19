#include "PointLightComponent.h"
#include "Game.h"
#include "RendererOGL.h"
#include "Mesh.h"
#include "LevelLoader.h"

PointLightComponent::PointLightComponent(Actor* owner) :
	Component(owner),
	diffuseColor{ 1.0f, 1.0f, 1.0f },
	innerRadius(1.0f),
	outerRadius(2.0f)
{
	Game::instance().getRenderer().addPointLight(this);
}

PointLightComponent::~PointLightComponent()
{
	Game::instance().getRenderer().removePointLight(this);
}

void PointLightComponent::draw(Shader& shader, Mesh& mesh)
{
	// We assume, coming into this function, that the shader is active
	// and the sphere mesh is active

	// World transform is scaled to the outer radius (divided by the mesh radius)
	// and positioned to the world position
	Matrix4 scale = Matrix4::createScale(owner.getScale() * outerRadius / mesh.getRadius());
	Matrix4 trans = Matrix4::createTranslation(owner.getPosition());
	Matrix4 worldTransform = scale * trans;
	shader.setMatrix4("uWorldTransform", worldTransform);
	// Set point light shader constants
	shader.setVector3f("uPointLight.worldPos", owner.getPosition());
	shader.setVector3f("uPointLight.diffuseColor", diffuseColor);
	shader.setFloat("uPointLight.innerRadius", innerRadius);
	shader.setFloat("uPointLight.outerRadius", outerRadius);

	// Draw the sphere
	glDrawElements(GL_TRIANGLES, mesh.getVertexArray()->getNbIndices(), GL_UNSIGNED_INT, nullptr);
}

void PointLightComponent::loadProperties(const rapidjson::Value& inObj)
{
	Component::loadProperties(inObj);
	JsonHelper::getVector3(inObj, "color", diffuseColor);
	JsonHelper::getFloat(inObj, "innerRadius", innerRadius);
	JsonHelper::getFloat(inObj, "outerRadius", outerRadius);
}
