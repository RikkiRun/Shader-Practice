#pragma once
#include <GL\glew.h>
#include <Vertex.h>

class Vertex;

struct ShapeDate
{
	ShapeDate() :
		vertices(0), numVertices(0),
		indices(0), numIndices(0){}
	Vertex* vertices;
	GLuint numVertices;
	GLushort* indices;
	GLuint numIndices;
	GLsizeiptr vertexBufferSize() const
	{
		return numVertices * sizeof(Vertex);
	}
	GLsizeiptr indexBufferSize() const
	{
		return numIndices * sizeof(GLushort);
	}

	void cleanup()
	{
		vertices = NULL;
		indices = NULL;
		numVertices = 0;
		numIndices = 0;
	}
};