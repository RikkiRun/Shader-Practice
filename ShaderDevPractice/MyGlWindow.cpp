#include <gl\glew.h>
#include <iostream>
#include <fstream>
#include <MyGlWindow.h>
#include <glm\glm.hpp>
#include <Vertex.h> 
#include <glm\gtx\transform.hpp>
#include <glm\gtc\matrix_transform.hpp>
#include <ShapeGenerator.h>
#include <cstdlib>
#include <ctime>
#include <QtGui\QMouseEvent>

using namespace std;
using glm::vec3;
using glm::mat4;

const uint NUM_VERTICES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 6;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(float);

extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;

GLuint programID;
GLuint numIndices;


void MyGlWindow::sendDataToOpenGL()
{
	ShapeDate shape = ShapeGenerator::makeCube();



	GLuint vertexBufferID; // vertex bufferID

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, shape.vertexBufferSize(), shape.vertices, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0); //position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0); //GL_FALSE: Not normalize data; stride: where the data begins, the first position to the second position

	
	// describe color attribute1
	glEnableVertexAttribArray(1); //color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(sizeof(float) * 3)); // last one: 2 float until we get to the beginning of the color data

	GLuint indexBufferID; // element bufferID
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, shape.indexBufferSize(), shape.indices, GL_STATIC_DRAW);
	
	numIndices = shape.numIndices;

	shape.cleanup();

	GLuint transformationMatrixBufferID;
	glGenBuffers(1, &transformationMatrixBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, transformationMatrixBufferID);
	
	mat4 projectionMartrix = glm::perspective(60.0f, ((float)width()) / height(), 0.1f, 10.0f);
	//cubeRotChange += 4;

	////??????????????????????????????????????????????????????????????????????
/*
	mat4 fullTransform[] =
	{
		 projectionMartrix * glm::translate(mat4(), vec3(0.0f, 1.0f, 3.0f))
			 * glm::rotate(mat4(), cubeRotChange, vec3(1.0f, 1.0f, 1.0f)),

		projectionMartrix * glm::translate(mat4(), vec3(0.0f, 0.0f, 0.0f))
			* glm::rotate(mat4(), cubeRotChange, vec3(0.0f, 1.0f, 0.0f))
	};

	
	////??????????????????????????????????????????????????????????????????????
*/

	mat4 fullTransform[] = 
	{
		projectionMartrix * glm::translate(vec3(-1.0f, 0.0f, -3.0f)) * glm::rotate(36.0f, vec3(1.0f, cubeRotChange, 0.0f)),
		projectionMartrix * glm::translate(vec3(1.0f, 0.0f, -3.75f)) * glm::rotate(126.0f, vec3(0.0f, 1.0f, 0.0f))
	};


	glBufferData(GL_ARRAY_BUFFER, sizeof(fullTransform), fullTransform, GL_STATIC_DRAW);
	//pointer: offset in the buffer
	glVertexAttribPointer(2, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 0));
	glVertexAttribPointer(3, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 4));
	glVertexAttribPointer(4, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 8));
	glVertexAttribPointer(5, 4, GL_FLOAT, GL_FALSE, sizeof(mat4), (void*)(sizeof(float) * 12));

	glEnableVertexAttribArray(2);
	glEnableVertexAttribArray(3);
	glEnableVertexAttribArray(4);
	glEnableVertexAttribArray(5);

	glVertexAttribDivisor(2, 1);
	glVertexAttribDivisor(3, 1);
	glVertexAttribDivisor(4, 1);
	glVertexAttribDivisor(5, 1);

}


bool checkStatus(GLint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType)
{

	GLint status; // only 1 status
	objectPropertyGetterFunc(objectID, statusType, &status);
	if (status != GL_TRUE) {
		GLint infoLogLength;
		objectPropertyGetterFunc(objectID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		getInfoLogFunc(objectID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;

		delete[] buffer;
		return false;
	}
	return true;

}

bool MyGlWindow::checkShaderStatus(GLuint shaderID)
{
	/*
	//get GLSL compiler error
	GLint compilerStatus; // only 1 status
	glGetShaderiv(shaderID, GL_COMPILE_STATUS, &compilerStatus);
	if (compilerStatus != GL_TRUE) {
		GLint infoLogLength;
		glGetShaderiv(shaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		glGetShaderInfoLog(shaderID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;

		delete[] buffer;
		return false;
	}
	return true;
	*/

	return checkStatus(shaderID, glGetShaderiv, glGetShaderInfoLog, GL_COMPILE_STATUS);
}

bool checkProgramStatus(GLuint programID)
{
	/*
	GLint linkStatus;
	glGetProgramiv(programID, GL_LINK_STATUS, &linkStatus);
	if (linkStatus != GL_TRUE) {
		GLint infoLogLength;
		glGetProgramiv(programID, GL_INFO_LOG_LENGTH, &infoLogLength);
		GLchar* buffer = new GLchar[infoLogLength];

		GLsizei bufferSize;
		glGetProgramInfoLog(programID, infoLogLength, &bufferSize, buffer);
		cout << buffer << endl;
		delete[] buffer;
		return false;
	}
	return true;
	*/
	return checkStatus(programID, glGetProgramiv, glGetProgramInfoLog, GL_LINK_STATUS);

}

string  MyGlWindow::readShaderCode(const char* fileName)
{
	ifstream meInput(fileName);
	if (!meInput.good()) {
		cout << "File failed to load ..." << fileName;
		exit(1);
	}

	return std::string(
		std::istreambuf_iterator<char>(meInput),
		std::istreambuf_iterator<char>()
	);
}


void MyGlWindow::installShaders()
{
	programID = glCreateProgram();

	GLuint vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
	GLuint fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);

	const GLchar* adapter[1];
	string temp = readShaderCode("VertexShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(vertexShaderID, 1, adapter, 0);
	temp = readShaderCode("FragmentShaderCode.glsl");
	adapter[0] = temp.c_str();
	glShaderSource(fragmentShaderID, 1, adapter, 0);

	glCompileShader(vertexShaderID);
	glCompileShader(fragmentShaderID);

	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID)) 
	{
		return;
	}

	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);

	//binding position before linking
	glBindAttribLocation(programID, 2, "position");

	glLinkProgram(programID);

	if (!checkProgramStatus(programID)) 
	{
		return;
	}

	GLint posiitonLocation = glGetAttribLocation(programID, "position");
	GLint colorLocation = glGetAttribLocation(programID, "vertexColor");
	GLint transformLocation = glGetAttribLocation(programID, "fullTransformMatrix");


	glDeleteShader(vertexShaderID);
	glDeleteShader(fragmentShaderID);


	glUseProgram(programID);
}

MyGlWindow::MyGlWindow()
{
	setMouseTracking(true);
}

void MyGlWindow::initializeGL() 
{
	glewInit();
	glEnable(GL_DEPTH_TEST);
	sendDataToOpenGL();
	installShaders();
}


void MyGlWindow::timerEvent(QTimerEvent *e)
{
	cubeRotChange += 4;
	printf("%f/n", cubeRotChange);
	repaint();
	
}

void MyGlWindow::mouseMoveEvent(QMouseEvent *event)
{
	printf("mouseTest");
}

void MyGlWindow::doNothinbg()
{
	printf("mouseDoNoting");
}

MyGlWindow::~MyGlWindow() 
{
	glUseProgram(0);
	glDeleteShader(programID);

}

void MyGlWindow::paintGL() 
{

	//but clearing buffer is expensive, so need to be cleared once
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());

	glDrawElementsInstanced(GL_TRIANGLES, numIndices, GL_UNSIGNED_SHORT, 0, 2);

} 