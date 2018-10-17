#include "Server.h"
#include <iostream>

Server::Server() {
	Game game;
}

Server::Server(string args[]) {
	Game game(args);
}