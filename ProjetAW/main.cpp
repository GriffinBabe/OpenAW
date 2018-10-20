#include "mainwindow.h"
#include <QApplication>
#include <QDebug>
#include "server.h"
#include "game.h"
#include <qstring.h>

int main(int argc, char *argv[])
{
	Game game; // Initialises the game model
	Player p("GriffinBabe"); //Creates an user
	game.setLocalPlayer(p);


    QApplication a(argc, argv);
    MainWindow w;
	w.setGame(game); // Sets the model to the window
	w.show();
    return a.exec();
}
