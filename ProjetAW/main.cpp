#include "mainwindow.h"
#include <QApplication>
#include <iostream>

int main(int argc, char *argv[])
{
	std::cout << "[Game Main] Printing args: ";
	for (int i = 0; i< argc; i++) {
		std::cout << argv[i] << ",";
	}
    std::cout << std::endl;

    Game game;
    Player* p = new Player("GriffinBabe", 'B'); // Adds a blue player
    game.addPlayer(p);
    Unit* u = new Infantery(3,3,p);
    game.addUnit(u);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setGame(&game);
    return a.exec();
}
