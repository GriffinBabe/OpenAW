#include "mainwindow.h"
#include <QApplication>
#include <iostream>

bool argPresent(std::string arg, std::vector<std::string> args) {
	// Copies all arguments into a container of strings
	for (std::string str : args) {
		if (arg.compare(str)) {
			return true;
		}
	}
	return false;
}

std::string getValue(std::string arg, std::vector<std::string> args) {
	std::string delimiter = "=";
	for (std::string str : args) {
		if (arg.compare(str.substr(0, str.find(delimiter)))==0) { // This one seems to return the opposite value, LIKE WHAT THE FUCK
			return str.substr(str.find(delimiter) + 1, str.length()-1);
		}
	}
	throw "Argument inexistant.";
}


int main(int argc, char *argv[])
{
	std::vector<std::string> allArgs(argv + 1, argv + argc); //  Array containing all strings of arguments

	/*
	 * In this case we are running a server, we will load the map from a file and we will have our mainwindow to connect to "localhost"
	 */
	if (argPresent("server", allArgs)) { // We expect to have a line like: server map=map1.txt username=user1 teamColor=R startMoney=6000
		std::cout << "Launching game as Server + Client" << std::endl;
		Game game(getValue("map", allArgs), std::stoi(getValue("startMoney", allArgs)));
		Network network(&game); // This is a server
		Player* p = new Player(getValue("username", allArgs), getValue("teamColor", allArgs).at(0));
		game.addPlayer(p); // We add the player which is the client that also launched the server !

		QApplication a(argc, argv);
		MainWindow w;
		w.show();
		w.setGame(&game, "localhost"); // We are setting the game to the view/controller and give it the local ip adress
	}
	/*
	 * In this case we are running a client, we will get all game inforamtions from server
	 */
	else if (argPresent("client", allArgs)) {
		std::cout << "Launching game as Client only" << std::endl;
		Game game(); // Empty as we don't know any informations (they will be given by the server in the NetworkClient class)

	}

	/*
	 * This is the local game dev mode
	 */
	else {
		Game game;
		Player* p = new Player("P1", 'B'); // Adds a blue player
		Player* p2 = new Player("P2", 'R'); // Adds a red player
		game.getBuildingOnPos(16,2)->setOwner(p);
		game.getBuildingOnPos(4,14)->setOwner(p2);

		game.getBuildingOnPos(16,4)->setOwner(p);
		game.getBuildingOnPos(15,3)->setOwner(p);

		game.getBuildingOnPos(4,12)->setOwner(p2);
		game.getBuildingOnPos(5,13)->setOwner(p2);


		game.addPlayer(p);
		game.addPlayer(p2);

		game.setLocalPlayer(p); // GriffinBabe is the local Player

		p->setMoney(6000);
		p2->setMoney(6000);

		QApplication a(argc, argv);
		MainWindow w;
		w.show();
		w.setGame(&game);
		return a.exec();
	}
}
