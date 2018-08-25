#pragma once
#ifndef MY_GL_WINDOW
#define MY_GL_WINDOW

#include <QtOpenGL\qglwidget>


class MyGlWindow : public QGLWidget
{
public:
	//MyGlWindow() { initializeGL(); };

protected:
	void initializeGL() override;
	void paintGL() override;
public:


};

#endif


