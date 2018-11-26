#pragma once
#include <ShapeData.h>
typedef unsigned int uint;

class ShapeGenerator
{
public:
	static ShapeDate makePlaneVerts(uint dimensions);
	static ShapeDate makePlaneIndices(uint dimensions);

	// Teapot helpers
	static void generatePatches(float * v, float * n, float * tc, unsigned short* el, int grid);
	static void moveLid(int grid, float *v, glm::mat4 lidTransform);
	static void buildPatchReflect(int patchNum,
		float *B, float *dB,
		float *v, float *n,
		float *tc, unsigned short *el,
		int &index, int &elIndex, int &tcIndex, int grid,
		bool reflectX, bool reflectY);
	static void buildPatch(glm::vec3 patch[][4],
		float *B, float *dB,
		float *v, float *n, float *tc,
		unsigned short *el,
		int &index, int &elIndex, int &tcIndex,
		int grid, glm::mat3 reflect,
		bool invertNormal);
	static void getPatch(int patchNum, glm::vec3 patch[][4], bool reverseV);
	static void computeBasisFunctions(float * B, float * dB, int grid);
	static glm::vec3 evaluate(int gridU, int gridV, float *B, glm::vec3 patch[][4]);
	static glm::vec3 evaluateNormal(int gridU, int gridV,
		float *B, float *dB, glm::vec3 patch[][4]);

	static ShapeDate makeTriangle();
	static ShapeDate makeCube();
	static ShapeDate makeArrow();
	static ShapeDate makePlane(uint dimensions = 10);
	static ShapeDate makeTeapot(uint tesslation = 10, const glm::mat4& lidTransform = glm::mat4());
	ShapeGenerator();
	~ShapeGenerator();
};
