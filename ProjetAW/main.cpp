#include "mainwindow.h"
#include <QApplication>
#include <iostream>
#include "networking/network.h"
#include <stdexcept>

bool argPresent(std::string arg, std::vector<std::string> args) {
	// Copies all arguments into a container of strings
	for (std::string str : args) {
		if (arg == str) {
			return true;
		}
	}
	return false;
}

std::string getValue(std::string arg, std::vector<std::string> args) {
	std::string delimiter = "=";
	for (std::string str : args) {
		if (arg == str.substr(0, str.find(delimiter))) { // This one seems to return the opposite value, LIKE WHAT THE FUCK
			return str.substr(str.find(delimiter) + 1, str.length()-1);
		}
	}
	throw std::invalid_argument("Can't find argument: " + arg);
}


int main(int argc, char *argv[])
{
/*    Game game;


	Player* p = new Player("GriffinBabe", 'B'); // Adds a blue player
	Player* p2 = new Player("Romain", 'R'); // Adds a red player
    IA* ia1 = new IA(2,p,&game); //crée une IA pour le joueur 1 (temporaire pour test)
    p->setIA(ia1);
    IA* ia2 = new IA(0,p2,&game); //crée une IA pour le joueur 2 (temporaire pour test)
    p2->setIA(ia2);

	game.getBuildingOnPos(16,2)->setOwner(p);
	game.getBuildingOnPos(4,14)->setOwner(p2);

	game.getBuildingOnPos(16,4)->setOwner(p);
	game.getBuildingOnPos(15,3)->setOwner(p);
    //game.getBuildingOnPos(20,8)->setOwner(p);*/
	std::vector<std::string> allArgs(argv + 1, argv + argc); //  Array containing all strings of arguments
	for (std::string str : allArgs) {
		std::cout << str << std::endl;
	}
	/*
	 * In this case we are running a server, we will load the map from a file and we will have our mainwindow to connect to "localhost"
	 */
	if (argPresent("server", allArgs)) { // We expect to have a line like: server map=map1.txt username=user1 teamColor=R startMoney=6000
		std::cout << "Launching game as Server + Client" << std::endl;
		QApplication a(argc, argv);
		Game * game = new Game(std::stoi(getValue("map", allArgs)), std::stoi(getValue("startMoney", allArgs)), std::stoi(getValue("income", allArgs))); // starts a new gale setting the map file path and the starting money
		Player* p = new Player(getValue("username", allArgs), getValue("teamColor", allArgs).at(0)); // creates the local player
		Player* p2 = new Player("otherplayer", getValue("teamColor", allArgs).at(0) == 'B' ? 'R' : 'B');
		game->addPlayer(p); // We add the player which is the client that also launched the server !
		game->setLocalPlayer(p);
		game->addPlayer(p2);

		Network network(game); // Launches the server

		MainWindow w;
		w.show();
		w.setGame(game, "127.0.0.1"); // We are setting the game to the view/controller and give it the local ip adress, even the local client uses a socket
		return a.exec();
	}

	/*
	 * In this case we are running a client, we will get all game informations from server
	 * But we already create a player and add it to the players vector
	 */
	else if (argPresent("client", allArgs)) { // We are expecting something like: client username=user2 teamColor=B ip=localhost

		QApplication a(argc, argv);
		Game* game = new Game(); // Empty as we don't know any informations (they will be given by the server in the NetworkClient class)
		Player* p = new Player(getValue("username", allArgs), getValue("teamColor", allArgs).at(0)); // We create a player with the launching parameters
		Player* p2 = new Player("otherplayer", getValue("teamColor", allArgs).at(0) == 'B' ? 'R' : 'B');

		std::string ip = getValue("ip", allArgs);
		game->addPlayer(p);
		game->setLocalPlayer(p);
		game->addPlayer(p2);
		MainWindow w;
		w.show();
		w.setGame(game, "127.0.0.1"); // We let localhost for testing purposes setGame2() will be called once network configuration is over
		return a.exec();
	}
	return 0;
}
