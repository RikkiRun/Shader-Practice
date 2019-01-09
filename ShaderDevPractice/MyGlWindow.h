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
	std::string readShaderCode(const char * fileName);
	void installShaders();
	MyGlWindow();
	~MyGlWindow();
	void doNothinbg();
	void loatTexture();
	void loadCubemap();
	static const char* TexFile[];

protected:
	void initializeGL() override;
	void paintGL() override;
	void timerEvent(QTimerEvent * e);
	void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *);

private:
	GLfloat teapotRotChange = +0.0f;

};

#endif


