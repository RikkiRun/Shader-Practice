#pragma once
#ifndef MY_GL_WINDOW
#define MY_GL_WINDOW

#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>


class MyGlWindow : public QGLWidget
{
public:
	void sendDataToOpenGL();
	bool checkShaderStatus(GLuint shaderID);
	bool checkProgramStatus(GLuint programID);
	std::string readShaderCode(const char * fileName);
	void installShaders();
	MyGlWindow();
	~MyGlWindow();


protected:
	void initializeGL() override;
	void paintGL() override;
	void timerEvent(QTimerEvent * e);

	void mouseMoveEvent(QMouseEvent *event);
public:
	void doNothinbg();

};

#endif


