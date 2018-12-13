#pragma once
#ifndef MY_GL_WINDOW
#define MY_GL_WINDOW
#include <random>
#include <QtOpenGL\qglwidget>


class MyGlWindow : public QGLWidget
{
public:
	//MyGlWindow() { initializeGL(); };
	GLfloat xStart = 0;
	GLfloat yStart = 0;
	
//	glm::vec2 Movement = glm::vec2(0, 0);
	GLfloat xMove = rand() / (float)RAND_MAX;
	GLfloat yMove = rand() / (float)RAND_MAX;
	void movement();

protected:
	void initializeGL() override;
	void paintGL() override;

	/*
public:
	MyGlWindow();
	~MyGlWindow();
	void InjectUniformValue(GLfloat X_Offset, GLfloat Y_Offset);
	void InjectUniformValue_2(GLfloat X_Offset, GLfloat Y_Offset);
	*/

private:

};

#endif


