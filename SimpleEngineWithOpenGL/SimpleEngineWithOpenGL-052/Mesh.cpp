#include "Mesh.h"
#include "VertexArray.h"
#include "Assets.h"

Mesh::Mesh() : vertexArray(nullptr), shaderName(""), radius(0.0f), specularPower(100.0f), box(Vector3::infinity, Vector3::negInfinity)
{
}

Mesh::~Mesh()
{
}

void Mesh::unload()
{
	delete vertexArray;
	vertexArray = nullptr;
}

void Mesh::addTexture(Texture* texture)
{
	textures.emplace_back(texture);
}

Texture* Mesh::getTexture(int index)
{
	if (index < textures.size())
	{
		return textures[index];
	}
	else
	{
		return nullptr;
	}
}

void Mesh::setTextures(const vector<Texture*>& texturesP)
{
	textures = texturesP;
}

void Mesh::setVertexArray(VertexArray* vertexArrayP)
{
	vertexArray = vertexArrayP;
}

void Mesh::setShaderName(string shaderNameP)
{
	shaderName = shaderNameP;
}

void Mesh::setRadius(float radiusP)
{
	radius = radiusP;
}

void Mesh::setSpecularPower(float specularPowerP)
{
	specularPower = specularPowerP;
}

void Mesh::setBox(const AABB& boxP)
{
	box = boxP;
}

void Mesh::setName(const string& nameP)
{
	name = nameP;
}

void Mesh::saveBinary(const std::string& filename, const void* verts, uint32_t numVerts, VertexArrayLayout layout, const uint32_t* indices, uint32_t numIndices, const std::vector<std::string>& textureNames, const AABB& box, float radius, float specPower, string shaderName)
{
	// Create header struct
	MeshBinHeader header;
	header.mbLayout = layout;
	header.mbNbTextures = static_cast<unsigned>(textureNames.size());
	header.mbNbVertices = numVerts;
	header.mbNbIndices = numIndices;
	header.mbBox = box;
	header.mbRadius = radius;
	//header.mbShaderName = shaderName;

	// Open binary file for writing
	std::ofstream outFile(filename, std::ios::out | std::ios::binary);
	if (outFile.is_open())
	{
		// Write the header
		outFile.write(reinterpret_cast<char*>(&header), sizeof(header));

		// For each texture, we need to write the size of the name
		// followed by the string (null-terminated)
		for (const auto& tex : textureNames)
		{
			// (Assume file names won't have more than 32k characters)
			uint16_t nameSize = static_cast<uint16_t>(tex.length()) + 1;
			outFile.write(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
			outFile.write(tex.c_str(), nameSize - 1);
			outFile.write("\0", 1);
		}

		// Figure out number of bytes for each vertex, based on layout
		unsigned vertexSize = VertexArray::getVertexSize(layout);
		// Write vertices
		outFile.write(reinterpret_cast<const char*>(verts),	numVerts * vertexSize);
		// Write indices
		outFile.write(reinterpret_cast<const char*>(indices), numIndices * sizeof(uint32_t));

		uint16_t nameSize = static_cast<uint16_t>(shaderName.length()) + 1;
		outFile.write(reinterpret_cast<char*>(&nameSize), sizeof(nameSize));
		outFile.write(shaderName.c_str(), nameSize - 1);
		outFile.write("\0", 1);
	}
}