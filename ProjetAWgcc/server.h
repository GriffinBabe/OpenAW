#ifndef SERVER_H
#define SERVER_H

#include "game.h"

class Server
{
private:
	char* argv; //pointer to the given arguments
public:
	Server();
	Server(char argv[]);
};

#endif // SERVER_H
