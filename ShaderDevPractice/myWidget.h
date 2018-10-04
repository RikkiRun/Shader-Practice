#pragma once
#ifndef MY_WIDGET
#define MY_WIDGET

#include <QtGui/qwidget.h>
#include <Qt/qevent.h>
#include <MyGlWindow.h>

#pragma once


class MyWidget : public QWidget
{
public:
	MyWidget();


protected:
	void keyPressEvent(QKeyEvent *);

private:
	MyGlWindow * myGLWindow;
};



#endif // !