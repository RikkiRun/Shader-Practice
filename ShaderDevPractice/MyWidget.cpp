#include "MyWidget.h"
#include <MyGlWindow.h>
#include <QtGui\qvboxlayout>
#include <QtGui\QHBoxLayout>
#include <qt\qevent.h>
 
MyWidget::MyWidget() {

	collided = FALSE;

	FlyingVector = glm::vec3(+0.01f, +0.02f, +0.0f);
	InitialPosition = glm::vec3(+0.0f, -3.0f, +0.0f);
	TriPosition = glm::vec3(+0.0f, -0.0f, +0.0f);
	OldTriPosition = glm::vec3(+0.0f, -0.0f, +0.0f);
	TriPosition.x = InitialPosition.x + FlyingVector.x;
	TriPosition.y = InitialPosition.y + FlyingVector.y;

	myGLWindow = new MyGlWindow();
	myGLWindow->movement();

	QVBoxLayout* mainLayout;
	setLayout(mainLayout = new QVBoxLayout);
	mainLayout->addWidget(myGLWindow);

	startTimer(20);

	//---Hard code boundaries---
	boundaryPoint1 = glm::vec3(-1.0f, 0.0f, +0.0f);
	boundaryPoint2 = glm::vec3(+1.0f, 0.0f, +0.0f);
	boundaryPoint3 = glm::vec3(+0.0f, 1.0f, +0.0f);
	boundaryPoint4 = glm::vec3(+0.0f, -1.0f, +0.0f);

}

void MyWidget::keyPressEvent(QKeyEvent *)
{
}

/*
void MyWidget::keyPressEvent(QKeyEvent *event)
{
	if (event->key() == Qt::Key_W)
	{
		myGLWindow->yPosition_1 += 0.1;
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_S)
	{
		myGLWindow->yPosition_1 -= 0.1;
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_A)
	{
		myGLWindow->xPosition_1 -= 0.1;
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_D)
	{
		myGLWindow->xPosition_1 += 0.1;
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_Right)
	{
		myGLWindow->xPosition_2 += 0.1;
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_Left)
	{
		myGLWindow->xPosition_2 -= 0.1;
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_Down)
	{
		myGLWindow->yPosition_2 -= 0.1;
		myGLWindow->repaint();
	}

	if (event->key() == Qt::Key_Up)
	{
		myGLWindow->yPosition_2 += 0.1;
		myGLWindow->repaint();
	}
}
*/

//----vector maths------
glm::vec3 MyWidget::perpCw3d(glm::vec3 input) {

	return glm::vec3(input.y, -input.x, +0.0f);
}

glm::vec3 MyWidget::perpCc3d(glm::vec3 input) {

	return glm::vec3(-input.y, input.x, +0.0f);
}

GLfloat MyWidget::dot2d(glm::vec2 input1, glm::vec2 input2)
{
	return input1.x*input2.x + input1.y*input2.y;
}

GLfloat MyWidget::dot3d(glm::vec3 input1, glm::vec3 input2)
{
	return input1.x*input2.x + input1.y*input2.y + input1.z*input2.z;
}

GLfloat MyWidget::vecMagnitude(glm::vec3 input) {

	return sqrt(input.x * input.x + input.y * input.y + input.z * input.z);
}

glm::vec3 MyWidget::normalize(glm::vec3 input)
{
	GLfloat mag = vecMagnitude(input);
	return glm::vec3(input.x / mag, input.y / mag, input.z / mag);
}

glm::vec3 MyWidget::scale(GLfloat scale, glm::vec3 input)
{
	return glm::vec3(input.x * scale, input.y * scale, input.z * scale);
}

glm::vec3 MyWidget::multiply(glm::vec3 left, glm::vec3 right)
{
	return glm::vec3(left.x*right.x, left.y*right.y, left.z*right.x);
}

glm::vec3 MyWidget::subtraction3d(glm::vec3 left, glm::vec3 right) {

	return glm::vec3(left.x - right.x, left.y - right.y, left.z - right.z);
}

glm::vec2 MyWidget::subtraction2d(glm::vec2 left, glm::vec2 right)
{
	return glm::vec2(left.x - right.x, left.y - right.y);
}

//--------vector maths------
void MyWidget::handleBoundaries()
{	//Left up wall
	glm::vec3 OldTriPosition = TriPosition;

	glm::vec3 wall1 = subtraction3d(boundaryPoint1, boundaryPoint3);
	glm::vec3 normal1 = normalize(perpCc3d(wall1));
	glm::vec3 respectivePosition = subtraction3d(TriPosition, boundaryPoint3);
	GLfloat dotResult = dot3d(normal1, respectivePosition);
	if (dotResult <= 0.0) {
		//		printf("collided with Left up wall with dot produce %f", dotResult);
		collided = true;
		FlyingVector = FlyingVector - 2 * dot3d(FlyingVector, normal1) * normal1;
		//FlyingVector = scale(+0.2f, FlyingVector);
	}
	else {
		collided = false;
	}

	//Left Down wall
	wall1 = subtraction3d(boundaryPoint1, boundaryPoint4);
	normal1 = normalize(perpCc3d(wall1));
	respectivePosition = subtraction3d(TriPosition, boundaryPoint4);
	dotResult = dot3d(normal1, respectivePosition);
	if (dotResult <= 0.0) {
		//		printf("collided with Left down wall with dot produce %f", dotResult);
		collided = true;
		FlyingVector = FlyingVector - 2 * dot3d(FlyingVector, normal1) * normal1;
		//FlyingVector = scale(+0.2f,FlyingVector);
	}
	else {
		collided = false;
	}

	//Right up wall
	wall1 = subtraction3d(boundaryPoint2, boundaryPoint3);
	normal1 = normalize(perpCc3d(wall1));
	respectivePosition = subtraction3d(TriPosition, boundaryPoint3);
	dotResult = dot3d(normal1, respectivePosition);
	if (dotResult <= 0.0) {
		//		printf("collided with Right Up wall with dot produce %f", dotResult);
		collided = true;
		FlyingVector = FlyingVector - 2 * dot3d(FlyingVector, normal1) * normal1;
		//FlyingVector = scale(+0.2f, FlyingVector);

	}
	else {
		collided = false;
	}

	//Right down wall
	wall1 = subtraction3d(boundaryPoint2, boundaryPoint4);
	normal1 = normalize(perpCc3d(wall1));
	respectivePosition = subtraction3d(TriPosition, boundaryPoint4);
	dotResult = dot3d(normal1, respectivePosition);
	if (dotResult <= 0.0) {
		//	printf("collided with Right Down wall with dot produce %f", dotResult);
		collided = true;
		FlyingVector = FlyingVector - 2 * dot3d(FlyingVector, normal1) * normal1;
		//FlyingVector = scale(+0.2f, FlyingVector);

	}
	else {
		collided = false;
	}
}

void MyWidget::timerEvent(QTimerEvent *event) {
	if (collided) {
		TriPosition = OldTriPosition;
	}
	TriPosition.x = TriPosition.x + FlyingVector.x;
	TriPosition.y = TriPosition.y + FlyingVector.y;
	OldTriPosition = TriPosition;
	myGLWindow->movement();
	handleBoundaries();
	myGLWindow->repaint();
}