#include "MyWidget.h"
#include <MyGlWindow.h>
#include <QtGui\qvboxlayout>
#include <QtGui\QHBoxLayout>
#include <qt\qevent.h>
 
MyWidget::MyWidget() {
	myGLWindow = new MyGlWindow();

	QVBoxLayout* mainLayout;
	setLayout(mainLayout = new QVBoxLayout);
	mainLayout->addWidget(myGLWindow);

}


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