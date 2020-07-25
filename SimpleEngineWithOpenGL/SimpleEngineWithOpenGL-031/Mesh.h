#pragma once
#include <string>
#include <vector>
#include "Texture.h"

using std::string;
using std::vector;

class Mesh
{
public:
	Mesh();
	~Mesh();

	void unload();

	class VertexArray* getVertexArray() { return vertexArray; }
	const string& getShaderName() const { return shaderName; }
	float getRadius() const { return radius; }
	float getSpecularPower() const { return specularPower; }

	void addTexture(Texture* texture);
	Texture* getTexture(int index);

	void setVertexArray(VertexArray* vertexArrayP);
	void setShaderName(const string& shaderNameP);
	void setRadius(float radiusP);
	void setSpecularPower(float specularPowerP);

private:
	vector<Texture*> textures;
	class VertexArray* vertexArray;
	string shaderName;
	float radius; // Bounding sphere radius
	float specularPower;
};

