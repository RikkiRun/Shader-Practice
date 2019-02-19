
#include <Qt\qapplication.h>
#include<MyGlWindow.h>
#include<QtGui/qwidget.h>
#include <MyWidget.h>


int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	MyGlWindow myWindow;
//	MyWidget myWidget;
//	myWidget.show();
	myWindow.show();
	myWindow.startTimer(20);
	myWindow.setFixedSize(800, 800);
	return app.exec();

}