#include "Server.h"
#include <iostream>

Server::Server() {
	this->game = *(new Game());
}