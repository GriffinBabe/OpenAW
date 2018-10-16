#pragma once
#include "Game.h"

class Server {
private:
	Game game;

public:
	Server();
	Server(string args[]);
};
