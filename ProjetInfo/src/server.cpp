#include <iostream>
#include "../include/server.h"
using namespace std;

Server::Server() {
	cout << "Server created" << endl;
	this->game = new AWGame({ "Server" });
}

Server::~Server() {
	cout << "Server destroyed" << endl;
}