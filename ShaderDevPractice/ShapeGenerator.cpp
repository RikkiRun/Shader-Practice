#include "ShapeGenerator.h"
#include <Vertex.h>
#include <glm.hpp>
#define NUM_ARRAY_ELEMENTS(a) sizeof(a) / sizeof(*a)
// get the size of the array and return the number of bytes in the array / the first element of the array


ShapeDate ShapeGenerator::makeTriangle()
{
	ShapeDate ret;

	Vertex theTri[] =
	{
		glm::vec3(-1.0f, +1.0f, +0.0f),
		glm::vec3(+0.6f, +0.0f, +0.8f),

		glm::vec3(-1.0f, +0.9f, +0.0f),
		glm::vec3(+0.8f, +0.0f, +0.2f),

		glm::vec3(-0.9f, +0.9f, +0.0f),
		glm::vec3(+0.5f, +0.0f, +0.7f),
	};

	ret.numVertices = NUM_ARRAY_ELEMENTS(theTri);
	ret.vertices = new Vertex[ret.numVertices];
	memcpy(ret.vertices, theTri, sizeof(theTri));

	//indices
	GLushort indices[] = { 0, 1, 2 }; // glushort for saving memory
	ret.numIndices = NUM_ARRAY_ELEMENTS(indices);
	ret.indices = new GLushort[ret.numIndices];
	memcpy(ret.indices, indices, sizeof(indices));

	return ret;
}