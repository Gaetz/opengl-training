#include "VertexArray.h"
#include <GL/glew.h>

VertexArray::VertexArray(const void* verticesP, unsigned int nbVerticesP, VertexArrayLayout layout, const unsigned int* indicesP, unsigned int nbIndicesP):
	nbVertices(nbVerticesP), nbIndices(nbIndicesP), vertexBuffer(0), indexBuffer(0), vertexArray(0)
{
	// Create vertex array
	glGenVertexArrays(1, &vertexArray);
	glBindVertexArray(vertexArray);

	unsigned vertexSize = 8 * sizeof(float);
	if (layout == VertexArrayLayout::PosNormSkinTex)
	{
		vertexSize = 8 * sizeof(float) + 8 * sizeof(char);
	}

	// Create vertex buffer
	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, nbVertices * vertexSize, verticesP, GL_STATIC_DRAW);

	// Create index buffer
	glGenBuffers(1, &indexBuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, nbIndicesP * sizeof(unsigned int), indicesP, GL_STATIC_DRAW);

	// Specify the vertex attributes
	if (layout == VertexArrayLayout::PosNormTex)
	{
		// Position is 3 floats starting at offset 0
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
		// Normal is 3 floats
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize, reinterpret_cast<void*>(sizeof(float) * 3));
		// Texture is 2 floats
		glEnableVertexAttribArray(2);
		glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, vertexSize, reinterpret_cast<void*>(sizeof(float) * 6));
	}
	else if (layout == VertexArrayLayout::PosNormSkinTex)
	{
		// Position is 3 floats
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, vertexSize, 0);
		// Normal is 3 floats
		glEnableVertexAttribArray(1);
		glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, vertexSize, reinterpret_cast<void*>(sizeof(float) * 3));
		// Skinning indices (keep as ints)
		glEnableVertexAttribArray(2);
		glVertexAttribIPointer(2, 4, GL_UNSIGNED_BYTE, vertexSize, reinterpret_cast<void*>(sizeof(float) * 6));
		// Skinning weights (convert to floats)
		glEnableVertexAttribArray(3);
		glVertexAttribPointer(3, 4, GL_UNSIGNED_BYTE, GL_TRUE, vertexSize, reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 4));
		// Texture coordinates
		glEnableVertexAttribArray(4);
		glVertexAttribPointer(4, 2, GL_FLOAT, GL_FALSE, vertexSize, reinterpret_cast<void*>(sizeof(float) * 6 + sizeof(char) * 8));
	}
}

VertexArray::~VertexArray()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteBuffers(1, &indexBuffer);
	glDeleteVertexArrays(1, &vertexArray);
}

void VertexArray::setActive()
{
	glBindVertexArray(vertexArray);
}

unsigned int VertexArray::getVertexSize(VertexArrayLayout layout)
{
	unsigned vertexSize = 8 * sizeof(float);
	if (layout == VertexArrayLayout::PosNormSkinTex)
	{
		vertexSize = 8 * sizeof(float) + 8 * sizeof(char);
	}
	return vertexSize;
}
