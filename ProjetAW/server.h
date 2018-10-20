#ifndef SERVER_H
#define SERVER_H
#include "game.h"

class Server
{
private:
	char* argv; //pointer to the given arguments
public:
	Server(char argv[]);
	Game game;
};

#endif // SERVER_H
