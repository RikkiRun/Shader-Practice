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
using glm::vec4;

const uint NUM_VERTICES_PER_TRI = 3;
const uint NUM_FLOATS_PER_VERTICE = 9;
const uint VERTEX_BYTE_SIZE = NUM_FLOATS_PER_VERTICE * sizeof(float);

extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;

GLuint programID;
GLuint teapotNumIndices;
GLuint arrowNumIndices;
GLuint planeNumIndices;

GLuint theBufferID;

GLuint teapotVertexArrayObjectID;
GLuint arrowVertexArrayObjectID;
GLuint planeVertexArrayObjectID;
GLuint teapotIndexDataByteOffset;
GLuint arrowIndexDataByteOffset;
GLuint planeIndexDataByteOffset;

//normals for plane, arrow and teapot
GLuint planeNormalIndices;
GLuint arrowNormalIndices;
GLuint teapotNormalIndices;
GLuint planeNormalsVertexArrayObjectID;
GLuint arrowNormalsVertexArrayObjectID;
GLuint teapotNormalVertexArrayObjectID;
GLuint planeNormalVertexArrayByteOffset;
GLuint arrowNormalVertexArrayByteOffset;
//GLuint teapotNormalVertexArrayByteOffset;

GLuint teapotNormalIndexDataByteOffset;
GLuint planeNormalIndexDataByteOffset;
GLuint arrowNormalIndexDataByteOffset;

GLuint fullTransformationUniformLocation;

Camera camera;

//load texture file 
const char * theTexture = "flower.jpg";


void MyGlWindow::sendDataToOpenGL()
{
	ShapeDate teapot = ShapeGenerator::makeTeapot();
	ShapeDate arrow = ShapeGenerator::makeArrow();
	ShapeDate plane = ShapeGenerator::makePlane(20);
	ShapeDate planeNormals = ShapeGenerator::generateNormals(plane);
	ShapeDate arrowNormals = ShapeGenerator::generateNormals(arrow);
	ShapeDate teapotNormals = ShapeGenerator::generateNormals(teapot);


	glGenBuffers(1, &theBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	glBufferData(GL_ARRAY_BUFFER,
		teapot.vertexBufferSize() + teapot.indexBufferSize() +
		arrow.vertexBufferSize() + arrow.indexBufferSize() +
		plane.vertexBufferSize() + plane.indexBufferSize() +
		planeNormals.vertexBufferSize() + planeNormals.indexBufferSize() +  
		arrowNormals.vertexBufferSize() + arrowNormals.indexBufferSize() +
		teapotNormals.vertexBufferSize() + teapotNormals.indexBufferSize(),
 		 0, GL_STATIC_DRAW);
	GLsizeiptr currentOffset = 0;
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, teapot.vertexBufferSize(), teapot.vertices);
	currentOffset += teapot.vertexBufferSize();
	teapotIndexDataByteOffset = currentOffset;
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, teapot.indexBufferSize(), teapot.indices);
	currentOffset += teapot.indexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrow.vertexBufferSize(), arrow.vertices);
	currentOffset += arrow.vertexBufferSize();
	arrowIndexDataByteOffset = currentOffset;
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrow.indexBufferSize(), arrow.indices);
	currentOffset += arrow.indexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, plane.vertexBufferSize(), plane.vertices);
	currentOffset += plane.vertexBufferSize();
	planeIndexDataByteOffset = currentOffset;
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, plane.indexBufferSize(), plane.indices);
	currentOffset += plane.indexBufferSize();

	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, teapotNormals.vertexBufferSize(), teapotNormals.vertices);
	currentOffset += teapotNormals.vertexBufferSize();
	teapotNormalIndexDataByteOffset = currentOffset;
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, teapotNormals.indexBufferSize(), teapotNormals.indices);
	currentOffset += teapotNormals.indexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrowNormals.vertexBufferSize(), arrowNormals.vertices);
	currentOffset += arrowNormals.vertexBufferSize();
	arrowNormalIndexDataByteOffset = currentOffset;
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, arrowNormals.indexBufferSize(), arrowNormals.indices);
	currentOffset += arrowNormals.indexBufferSize();
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, planeNormals.vertexBufferSize(), planeNormals.vertices);
	currentOffset += planeNormals.vertexBufferSize();
	planeNormalIndexDataByteOffset = currentOffset;
	glBufferSubData(GL_ARRAY_BUFFER, currentOffset, planeNormals.indexBufferSize(), planeNormals.indices);
	currentOffset += planeNormals.indexBufferSize();



	teapotNumIndices = teapot.numIndices;
	arrowNumIndices = arrow.numIndices;
	planeNumIndices = plane.numIndices;
	teapotNormalIndices = teapotNormals.numIndices;
	arrowNormalIndices = arrowNormals.numIndices;
	planeNormalIndices = planeNormals.numIndices;

	glGenVertexArrays(1, &teapotVertexArrayObjectID);
	glGenVertexArrays(1, &arrowVertexArrayObjectID);
	glGenVertexArrays(1, &planeVertexArrayObjectID);
	glGenVertexArrays(1, &teapotNormalVertexArrayObjectID);
	glGenVertexArrays(1, &arrowNormalsVertexArrayObjectID);
	glGenVertexArrays(1, &planeNormalsVertexArrayObjectID);


	glBindVertexArray(teapotVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(sizeof(float) * 3));
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);
	
	
	glBindVertexArray(arrowVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint arrowByteOffset = teapot.vertexBufferSize() + teapot.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)arrowByteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(arrowByteOffset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(arrowByteOffset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

	glBindVertexArray(planeVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint planByteOffset = arrowByteOffset + arrow.vertexBufferSize() + arrow.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)planByteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(planByteOffset + sizeof(float) * 3));
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(planByteOffset + sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);


	glBindVertexArray(teapotNormalVertexArrayObjectID);
	glEnableVertexAttribArray(0);
	glEnableVertexAttribArray(1);
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
	GLuint teapotNormalsByteOffset = planByteOffset + plane.vertexBufferSize() + plane.indexBufferSize();
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)teapotNormalsByteOffset);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (void*)(teapotNormalsByteOffset + sizeof(float) * 3));
//	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(sizeof(float) * 6));
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, theBufferID);

//	glBindVertexArray(arrowNormalsVertexArrayObjectID);
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
//	GLuint arrowNormalsByteOffset = teapotNormalsByteOffset + arrowNormals.vertexBufferSize() + arrowNormals.indexBufferSize();
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(sizeof(float) * 3));

//	glBindVertexArray(planeNormalsVertexArrayObjectID);
//	glEnableVertexAttribArray(0);
//	glEnableVertexAttribArray(1);
//	glBindBuffer(GL_ARRAY_BUFFER, theBufferID);
//	GLuint planeNormalsByteOffset = arrowNormalsByteOffset + planeNormals.vertexBufferSize() + planeNormals.indexBufferSize();
//	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, 0);
//	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, VERTEX_BYTE_SIZE, (char*)(sizeof(float) * 3));

	teapotIndexDataByteOffset = teapot.vertexBufferSize();
	arrowIndexDataByteOffset = arrowByteOffset + arrow.vertexBufferSize();
	planeIndexDataByteOffset = planByteOffset + plane.vertexBufferSize();
	teapotNormalIndexDataByteOffset = teapotNormalsByteOffset + teapotNormals.vertexBufferSize();


	teapot.cleanup();
	arrow.cleanup();
	plane.cleanup();
	teapotNormals.cleanup();
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
	//	GLint transformLocation = glGetAttribLocation(programID, "modelToProjectionMatrix");


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
	setMaximumSize(1200, 600);
	glewInit();
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	sendDataToOpenGL();
	installShaders();
	fullTransformationUniformLocation = glGetUniformLocation(programID, "modelToProjectionMatrix");
}


void MyGlWindow::timerEvent(QTimerEvent *e)
{
	teapotRotChange += 4;
//	printf("%f/n", teapotRotChange);
	repaint();

}

void MyGlWindow::mouseMoveEvent(QMouseEvent* event)
{
	camera.mouseUpdate(glm::vec2(event->x(), event->y()));

	//	printf("mouseTest");
}

void MyGlWindow::doNothinbg() 
{
//	printf("mouseDoNoting"); //testing mouse 
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


void MyGlWindow::paintGL()
{
	//but clearing buffer is expensive, so need to be cleared once
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());
	

	mat4 modelToProjectionMatrix;
	mat4 viewToProjectionMatrix =
		glm::perspective(60.0f, ((float)width()) / height(), 0.1f, 20.0f);
	mat4 worldToViewMatrix = camera.getWorldToViewMatrix();
	mat4 worldToProjectionMatrix = viewToProjectionMatrix * worldToViewMatrix;

	//add ambient light
	GLint ambientLightUniformLocation = glGetUniformLocation(programID, "ambientLight");
	vec4 ambientLight(0.1f, 0.1f, 0.5f, 1.0f);
	glUniform4fv(ambientLightUniformLocation, 1, &ambientLight[0]);

	// add specular light
	GLint eyePositionWorldUniformLocation = glGetUniformLocation(programID, "eyePositionWorld");
	glm::vec3 eyePosition = camera.getPostion();
	glUniform3fv(eyePositionWorldUniformLocation, 1, &eyePosition[0]);

	//add light position
	GLint lightPositionWorldUniformPosition = glGetUniformLocation(programID, "lightPositionWorld");
	glm::vec3 lightPositionWorld(0.0f, 1.0f, 0.0f);
	glUniform3fv(lightPositionWorldUniformPosition, 1, &lightPositionWorld[0]);

	// model transform matrix 
	GLint modelToWorldTransformMatrixUniformLocation =
		glGetUniformLocation(programID, "modelToWorldMatrix");



	// teapots
	glBindVertexArray(teapotVertexArrayObjectID);
	mat4 teapot1modelToWorldMatrix =
		glm::translate(vec3(-3.0f, 0.0f, -6.0f)) * glm::rotate(0.0f, vec3(1.0f, 0.0f, 0.0f));
	modelToProjectionMatrix = worldToProjectionMatrix * teapot1modelToWorldMatrix;
	glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &modelToProjectionMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, teapotNumIndices, GL_UNSIGNED_SHORT, (void*)teapotIndexDataByteOffset);

	mat4 teapot2ModelToWorldMatrix =
		glm::translate(vec3(3.0f, 0.0f, -6.75f)) * glm::rotate(0.0f, vec3(1.0f, 0.0f, 0.0f));
	modelToProjectionMatrix = worldToProjectionMatrix * teapot2ModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &modelToProjectionMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, teapotNumIndices, GL_UNSIGNED_SHORT, (void*)teapotIndexDataByteOffset);

	// arrow 
	glBindVertexArray(arrowVertexArrayObjectID);
	mat4 arrowModelToWorldMatrix =
		glm::translate(0.0f, 0.0f, -3.0f);
	modelToProjectionMatrix = worldToProjectionMatrix * arrowModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &modelToProjectionMatrix[0][0]);
	glUniformMatrix4fv(modelToWorldTransformMatrixUniformLocation, 1, GL_FALSE,
		&arrowModelToWorldMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, arrowNumIndices, GL_UNSIGNED_SHORT, (void*)arrowIndexDataByteOffset);

	//plane
	glBindVertexArray(planeVertexArrayObjectID);
	mat4 planeModelToWorldMatrix;
	modelToProjectionMatrix = worldToProjectionMatrix * planeModelToWorldMatrix;
	glUniformMatrix4fv(fullTransformationUniformLocation, 1, GL_FALSE, &modelToProjectionMatrix[0][0]);
	glUniformMatrix4fv(modelToWorldTransformMatrixUniformLocation, 1, GL_FALSE,
		&planeModelToWorldMatrix[0][0]);
	glDrawElements(GL_TRIANGLES, planeNumIndices, GL_UNSIGNED_SHORT, (void*)planeIndexDataByteOffset);

	// teapot normals
	glBindVertexArray(teapotNormalVertexArrayObjectID);
	glDrawElements(GL_LINE, teapotNormalIndices, GL_UNSIGNED_SHORT, (void*)teapotNormalIndexDataByteOffset);
	
//	printf(" %f/n", teapotNormalIndices);
	 
	// arrow normals
//	glDrawElements(GL_LINE, arrowNormalIndices, GL_UNSIGNED_SHORT, (void*)arrowNormalVertexArrayByteOffset);

	// plane normals
//	glDrawElements(GL_LINE, planeNormalIndices, GL_UNSIGNED_SHORT, (void*)planeNormalVertexArrayByteOffset);
}


MyGlWindow::~MyGlWindow()
{
	glDeleteBuffers(1, &theBufferID);
	glUseProgram(0);
	glDeleteShader(programID);
}