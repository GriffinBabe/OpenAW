#include "session.h"
#include <iostream>

Session::Session(Player* p, Game* g, QTcpSocket* s) {
	this->player = p;
	this->game = g;
	this->socket = s;
}

Session::~Session()
{

}

void Session::onData()
{
	std::cout << "[Server Session] Received data from client " << this->player->getUsername() << std::endl;
}

void Session::onDisconnection()
{
	std::cout << "[Server Session] Client " << this->player->getUsername() << " disconnected!" << std::endl;
}
