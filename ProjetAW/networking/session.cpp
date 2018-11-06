#include "session.h"

Session::Session(Player* p, Game* g, QTcpSocket* s) {
	this->player = p;
	this->game = g;
	this->socket = s;
}

void Session::run()
{
	while (true) {

	}
}
