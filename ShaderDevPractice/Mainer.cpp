
#include <Qt\qapplication.h>
#include<MyGlWindow.h>
#include <MyWidget.h>


int main(int argc, char* argv[]) {
	QApplication app(argc, argv);
	MyGlWindow myWindow;
	MyWidget myWidget;

	myWidget.setFixedSize(512, 512);
	myWidget.show();

	//myWindow.show();
	return app.exec();
}