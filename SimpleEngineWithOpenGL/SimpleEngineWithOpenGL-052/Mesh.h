#pragma once
#include <string>
#include <vector>
#include "Texture.h"
#include "AABB.h"

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
	const AABB& getBox() const { return box; }
	const string& getName() const { return name; }

	void addTexture(Texture* texture);
	Texture* getTexture(int index);
	void setTextures(const vector<Texture*>& texturesP);

	void setVertexArray(VertexArray* vertexArrayP);
	void setShaderName(string shaderNameP);
	void setRadius(float radiusP);
	void setSpecularPower(float specularPowerP);
	void setBox(const AABB& boxP);
	void setName(const string& nameP);


	void saveBinary(const std::string& fileName, const void* verts,
		uint32_t numVerts, VertexArrayLayout layout,
		const uint32_t* indices, uint32_t numIndices,
		const std::vector<std::string>& textureNames,
		const AABB& box, float radius,
		float specPower, string shaderName);

private:
	vector<Texture*> textures;
	class VertexArray* vertexArray;
	string shaderName;
	float radius; // Bounding sphere radius
	float specularPower;
	AABB box;
	string name;
};

