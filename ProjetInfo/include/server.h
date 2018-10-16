#ifndef Server_H
#define Server_H

#include <iostream>
#include "awgame.h"

class Server {
	/*
		This is the core of the networking part
	*/
private:
	AWGame* game;
public:
	Server();
	~Server();
};

#endif