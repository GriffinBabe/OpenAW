#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "map.h"

int main(int argc, char *argv[])
{
	std::cout << "[Game Main] Printing args: ";
	for (int i = 0; i< argc; i++) {
		std::cout << argv[i] << ",";
	}
    std::cout << "test" << std::endl;
    Map(":/Maps/map1.txt");

    //Game game;

    //QApplication a(argc, argv);
    //MainWindow w;
    //w.show();
    //w.setGame(&game);
    //return a.exec();
}
