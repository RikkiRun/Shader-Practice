#pragma once
#ifndef MY_GL_WINDOW
#define MY_GL_WINDOW

#include <QtOpenGL\qglwidget>


class MyGlWindow : public QGLWidget
{
protected:
	void initializeGL();
	void paintGL();
public:
};

#endif


