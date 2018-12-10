
#include <Qt\qapplication.h>
#include<MyGlWindow.h>
#include<QtGui/qwidget.h>



int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	MyGlWindow myWindow;
	QWidget myWidget;
//	myWidget.show();
	myWindow.show();
	myWindow.startTimer(20);
	return app.exec();

}