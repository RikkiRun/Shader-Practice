#pragma once
#ifndef MY_GL_WINDOW
#define MY_GL_WINDOW

#include <QtOpenGL\qglwidget>


class MyGlWindow : public QGLWidget
{
public:
	//MyGlWindow() { initializeGL(); };
//	GLfloat xPosition_1 = 0.3f;
//	GLfloat yPosition_1 = -0.3f;
//	GLfloat xPosition_2 = 0.5f;
//	GLfloat yPosition_2 = -0.5f;

	void initialValueSetter(GLfloat xStart, GLfloat yStart);
	void injectUniformValue(GLfloat xOffset, GLfloat yOffset);
	void injectUniformValue_2(GLfloat xOffset, GLfloat yOffset);

protected:
	void initializeGL() override;
	void paintGL() override;

private:
	GLfloat xStart = 0.0f;
	GLfloat yStart = 0.0f;
	GLfloat xStart2 = 0.0f;
	GLfloat yStart2 = 0.0f;

};

#endif