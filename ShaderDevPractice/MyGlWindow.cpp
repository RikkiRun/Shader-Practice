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
#include <QtGui\QKeyEvent>
#include "Camera.h"

using namespace std;
using glm::vec3;
using glm::mat4;

const uint NUM_VERTICES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 6;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(float);

extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;

GLuint programID;
GLuint cubeNumIndices;
GLuint arrowNumIndices;

GLuint theBufferID;

GLuint cubeVertexArrayObjectID;
GLuint arrowVertexArrayObjectID;
GLuint cubeIndexDataByteOffset;
GLuint arrowIndexDataByteOffset;

GLuint fullTransformationUniformLocation;

Camera camera;



void MyGlWindow::sendDataToOpenGL()
{
	ShapeDate cube = ShapeGenerator::makeCube();
	ShapeDate arrow = ShapeGenerator::makeArrow();

	glGenBuffers(1, &theBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	glBufferData(GL_ARRAY_BUFFER,
		cube.vertexBufferSize() + cube.indexBufferSize() + 
		arrow.vertexBufferSize() + arrow.indexBufferSize(), 0, GL_STATIC_DRAW);
	GLsizeiptr currentOffset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cube.vertexBufferSize(), cube.vertices);
	currentOffset += cube.vertexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, cube.indexBufferSize(), cube.indices);
	currentOffset += cube.indexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrow.vertexBufferSize(), arrow.vertices);
	currentOffset += arrow.vertexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrow.indexBufferSize(), arrow.indices);


	cubeNumIndices = cube.numIndices;
	arrowNumIndices = arrow.numIndices;

	glGenVertexArrays(1, &cubeVertexArrayObjectID);
	glGenVertexArrays(1, &arrowVertexArrayObjectID);

	glBindVertexArray(cubeVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(sizeof(float) * 3));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	glBindVertexArray(arrowVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint arrowByteOffset = cube.vertexBufferSize() + cube.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)arrowByteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(arrowByteOffset + sizeof(float) * 3));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);
	cubeIndexDataByteOffset = cube.vertexBufferSize();
	arrowIndexDataByteOffset = arrowByteOffset + arrow.vertexBufferSize();

	cube.cleanup();
	arrow.cleanup();
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
//	glBindAttribLocation(programID, 2, "position");

	glLinkProgram(programID);

	if (!checkProgramStatus(programID)) 
	{
		return;
	}

	//	GLint posiitonLocation = glGetAttribLocation(programID, "position");
	//	GLint colorLocation = glGetAttribLocation(programID, "vertexColor");
	//	GLint transformLocation = glGetAttribLocation(programID, "fullTransformMatrix");


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
	fullTransformationUniformLocation = glGetUniformLocation(programID, "fullTransformMatrix");
}


void MyGlWindow::timerEvent(QTimerEvent *e)
{
	cubeRotChange += 4;
	printf("%f/n", cubeRotChange);
	repaint();
	
}

void MyGlWindow::mouseMoveEvent(QMouseEvent* event)
{
	camera.mouseUpdate(glm::vec2(event->x(), event->y()));

//	printf("mouseTest");
}

void MyGlWindow::doNothinbg()
{
	printf("mouseDoNoting"); //testing mouse 
}

void MyGlWindow::keyPressEvent(QKeyEvent* e) 
{
	switch (e->key())
	{
	case Qt::Key::Key_W:
		camera.moveForward();
		break;
	case Qt::Key::Key_S:
		camera.moveBackward();
		break;
	case Qt::Key::Key_A:
		camera.strafeLeft();
		break;
	case Qt::Key::Key_D:
		camera.strafeRight();
		break;
	case Qt::Key::Key_R:
		camera.moveUp();
		break;
	case Qt::Key::Key_F:
		camera.moveDown();
		break;
	}
	repaint();
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

	mat4 fullTransformMatrix;
	mat4 viewToProjectionMatrix = 
		glm::perspective(60.0f, ((float)width()) / height(), 0.1f, 10.0f);
	mat4 worldToViewMatrix = camera.getWorldToViewMatrix();
	mat4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;


	// cubes
	glBindVertexArray(cubeVertexArrayObjectID);
	mat4 cube1modelToWorldMatrix = 
		glm::translate(vec3(-2.0f, 0.0f, -3.0f)) * glm::rotate(36.0f, vec3(1.0f, 0.0f, 0.0f));
	fullTransformMatrix = worldToProjectionMatrix * cube1modelToWorldMatrix;
	glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, (void*)cubeIndexDataByteOffset);

	mat4 cube2ModelToWorldMatrix = 
		glm::translate(vec3(2.0f, 0.0f, -3.75f)) * glm::rotate(126.0f, vec3(0.0f, 1.0f, 0.0f));
	fullTransformMatrix = worldToProjectionMatrix * cube2ModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, cubeNumIndices, GL_UNSIGNED_SHORT, (void*)cubeIndexDataByteOffset);

	// arrow 
	
	glBindVertexArray(arrowVertexArrayObjectID);
	mat4 arrowModelToWorldMatrix = 
		glm::translate(0.0f, 0.0f, -3.0f);
	fullTransformMatrix = worldToProjectionMatrix * arrowModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &fullTransformMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, arrowNumIndices, GL_UNSIGNED_SHORT, (void*)arrowIndexDataByteOffset);

} 