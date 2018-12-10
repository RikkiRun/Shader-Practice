#include "MyWidget.h"
#include <MyGlWindow.h>
#include <QtGui\qvboxlayout>
#include <QtGui\QHBoxLayout>
#include <QtGui\qhboxlayout>
#include <QtGui\qapplication.h>
#include <QtGui/qwidget.h>


MyWidget::MyWidget() {
	QVBoxLayout* mainLayout = new QVBoxLayout();
	setLayout(mainLayout);
	QVBoxLayout* controlsLayout;
	mainLayout->addLayout(controlsLayout = new QVBoxLayout);
	mainLayout->addWidget(new MyGlWindow);
}

MyWidget::~MyWidget()
{

}
