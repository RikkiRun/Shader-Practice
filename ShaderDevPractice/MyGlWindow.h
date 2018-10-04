#pragma once
#ifndef MY_GL_WINDOW
#define MY_GL_WINDOW

#include <QtOpenGL\qglwidget>


class MyGlWindow : public QGLWidget
{
public:
	//MyGlWindow() { initializeGL(); };
	GLfloat xPosition_1 = 0.3f;
	GLfloat yPosition_1 = -0.3f;
	GLfloat xPosition_2 = 0.5f;
	GLfloat yPosition_2 = -0.5f;
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


