#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include <QResource>

int main(int argc, char *argv[])
{
	std::cout << "[Game Main] Printing args: ";
	for (int i = 0; i< argc; i++) {
		std::cout << argv[i] << ",";
	}
    std::cout << std::endl;

    QResource::registerResource("resources.qrc");

	QApplication a(argc, argv);
	MainWindow w;
    w.show();
    map(":/Maps/map1.txt");
	return a.exec();
}
