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
	Player* p2 = new Player("Romain", 'R'); // Adds a red player
    IA* ia1 = new IA(1,p2,&game); //crée une IA pour le joueur 2 (temporaire)
	game.getBuildingOnPos(16,2)->setOwner(p);
	game.getBuildingOnPos(4,14)->setOwner(p2);

	game.getBuildingOnPos(16,4)->setOwner(p);
	game.getBuildingOnPos(15,3)->setOwner(p);
    game.getBuildingOnPos(20,8)->setOwner(p);


	game.getBuildingOnPos(4,12)->setOwner(p2);
	game.getBuildingOnPos(5,13)->setOwner(p2);


    game.addPlayer(p);
	game.addPlayer(p2);

	game.setLocalPlayer(p); // GriffinBabe is the local Player

    p->setMoney(1000000);
    p2->setMoney(6000);

    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    w.setGame(&game);
    return a.exec();
}
