#ifndef Server_H
#define Server_H

#include <iostream>
#include "awgame.h"

class Server {
private:
	AWGame* game;
public:
	Server();
	~Server();
};

#endif