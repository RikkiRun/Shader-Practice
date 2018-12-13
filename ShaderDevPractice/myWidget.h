#pragma once
#ifndef MY_WIDGET
#define MY_WIDGET
#include <QtGui\qwidget.h>
#include <Qt\qevent.h>
#include <MyGLWindow.h>
#include <glm\glm.hpp>

#pragma once


class MyWidget : public QWidget
{
public:
	MyWidget();


	glm::vec3 scale(GLfloat scale, glm::vec3 input);
	glm::vec3 multiply(glm::vec3 left, glm::vec3 right);
	glm::vec3 subtraction3d(glm::vec3 left, glm::vec3 right);
	glm::vec2 subtraction2d(glm::vec2 left, glm::vec2 right);
	glm::vec3 perpCw3d(glm::vec3 input);
	glm::vec3 perpCc3d(glm::vec3 input);
	GLfloat dot2d(glm::vec2 input1, glm::vec2 input2);
	GLfloat dot3d(glm::vec3 input1, glm::vec3 input2);
	GLfloat vecMagnitude(glm::vec3 input);
	glm::vec3 normalize(glm::vec3 input);

	void handleBoundaries();


protected:
	void keyPressEvent(QKeyEvent *);
	void timerEvent(QTimerEvent *event);

private:
	MyGlWindow * myGLWindow;
	glm::vec3 InitialPosition;
	glm::vec3 FlyingVector;
	glm::vec3 TriPosition;
	glm::vec3 OldTriPosition;

	bool collided;

	glm::vec3 boundaryPoint1;
	glm::vec3 boundaryPoint2;
	glm::vec3 boundaryPoint3;
	glm::vec3 boundaryPoint4;
};



#endif // !