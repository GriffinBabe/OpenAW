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
	Player* p2 = new Player("Stefano", 'R'); // Adds a red player
    game.addPlayer(p);
	game.addPlayer(p2);
    Unit* u = new Infantery(3,3,p);
	Unit* u2 = new Infantery(3,4,p2);
    game.addUnit(u);
	game.addUnit(u2);
	game.setLocalPlayer(p); // GriffinBabe is the local Player

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setGame(&game);
    return a.exec();
}
