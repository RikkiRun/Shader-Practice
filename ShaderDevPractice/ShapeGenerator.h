#pragma once
#include <ShapeData.h>
typedef unsigned int uint;

class ShapeGenerator
{
public:
	static ShapeDate makePlaneVerts(uint dimensions);
	static ShapeDate makePlaneIndices(uint dimensions);
	static ShapeDate makeTriangle();
	static ShapeDate makeCube();
	static ShapeDate makeArrow();
	static ShapeDate makePlane(uint dimensions = 10);
	static ShapeDate makeTeapot(uint tesslation = 10, const glm::mat4& lidTransform = glm::mat4());
	ShapeGenerator();
	~ShapeGenerator();
};
