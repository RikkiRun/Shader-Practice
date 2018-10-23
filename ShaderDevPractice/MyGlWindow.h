#pragma once
#ifndef MY_GL_WINDOW
#define MY_GL_WINDOW

#include <QtOpenGL\qglwidget>
#include <Qt\qtimer.h>


class MyGlWindow : public QGLWidget
{
public:
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


