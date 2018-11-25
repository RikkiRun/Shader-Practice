#pragma once
#include <ShapeData.h>
class ShapeGenerator
{
public:
	static ShapeDate makeTriangle();
	static ShapeDate makeCube();
	static ShapeDate makeArrow();
	ShapeGenerator();
	~ShapeGenerator();
};
