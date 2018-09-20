#include <gl\glew.h>
#include <iostream>
#include <fstream>
#include <MyGlWindow.h>
using namespace std;

extern const char* vertexShaderCode;
extern const char* fragmentShaderCode;

GLfloat xPosition = 0.0f;
GLuint programID;

void sendDataToOpenGL() {


	GLfloat theTri[] = {
	-1.0f, 1.0f, 0.0f,
	0.6f, 0.0f, 0.8f,

	-1.0f, 0.9f, 0.0f,
	0.8f, 0.0f, 0.2f,

	-0.9f, 0.9f, 0.0f,
	0.5f, 0.0f, 0.7f,
	};


	GLuint vertexBufferID; // vertex bufferID

	glGenBuffers(1, &vertexBufferID);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBufferID);
	glBufferData(GL_ARRAY_BUFFER, sizeof(theTri), theTri, GL_STATIC_DRAW);
	//glBufferData(GL_ARRAY_BUFFER, MAX_TRIS * TRIANGLE_BYTE_SIZE, NULL, GL_STATIC_DRAW);
	glEnableVertexAttribArray(0); //position
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, 0); //GL_FALSE: Not normalize data; stride: where the data begins, the first position to the second position

	// describe color attribute1
	glEnableVertexAttribArray(1); //color
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 6, (char*)(sizeof(float) * 3)); // last one: 2 float until we get to the beginning of the color data


	//indices
	GLushort indices[] = { 0, 1, 2 }; // glushort for saving memory
	GLuint indexBufferID; // element bufferID
	glGenBuffers(1, &indexBufferID);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);
}

/*
void sendAnotherTriToOpenGL() {

	GLfloat thisTri[] = {
		1.0f, 1.0f, 0.0f,
		0.6f, 0.0f, 0.8f,

		 0.0f, 1.0f, 0.0f,
		0.8f, 0.0f, 0.2f,

		 -1.0f, 0.0f, 0.0f,
		0.5f, 0.0f, 0.7f,
	};

	glBufferSubData(GL_ARRAY_BUFFER,
		TRIANGLE_BYTE_SIZE * numTris, TRIANGLE_BYTE_SIZE, thisTri);
	numTris++;
}
*/


bool checkStatus(GLint objectID,
	PFNGLGETSHADERIVPROC objectPropertyGetterFunc,
	PFNGLGETSHADERINFOLOGPROC getInfoLogFunc,
	GLenum statusType) {

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

bool checkShaderStatus(GLuint shaderID) {
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

bool checkProgramStatus(GLuint programID) {
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

string  readShaderCode(const char* fileName) {
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


void installShaders() {
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

	if (!checkShaderStatus(vertexShaderID) || !checkShaderStatus(fragmentShaderID)) {
		return;
	}

	glAttachShader(programID, vertexShaderID);
	glAttachShader(programID, fragmentShaderID);
	glLinkProgram(programID);

	if (!checkProgramStatus(programID)) {
		return;
	}

	glUseProgram(programID);
}

void MyGlWindow::initializeGL() {
	glewInit();
	glEnable(GL_DEPTH_TEST);
	sendDataToOpenGL();
	installShaders();
}


 

void MyGlWindow::paintGL() {

	//but clearing buffer is expensive, so need to be cleared once
	glClear(GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
	glViewport(0, 0, width(), height());


	GLint xMoveUniformLocation = glGetUniformLocation(programID, "xMove");
	GLint yMoveUniformLocation = glGetUniformLocation(programID, "yMove");

	xPosition += 0.1;
	//glClear(GL_DEPTH_BUFFER_BIT);
	//glClear(GL_COLOR_BUFFER_BIT); //there's a back buffer and a front buffer, if not clear, it will switch

	glUniform1f(xMoveUniformLocation, xPosition);
	glUniform1f(yMoveUniformLocation, -0.9f);
//	glUniform1f(xMoveUniformLocation, 0.0f);



	//glDrawArrays(GL_TRIANGLES, 0, 3);
	//draw a triangle
	glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, 0);
}
/*
//draw a new triangle every new frame
	sendAnotherTriToOpenGL();
	glDrawArrays(GL_TRIANGLES, (numTris - 1) * NUM_VERTICES_PER_TRI,
		numTris * NUM_VERTICES_PER_TRI);
	}
	*/
	//uniform position --> keyboard movement 