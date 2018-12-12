#include "network.h"
#include <iostream>
#include "QTcpSocket"

Network::Network(Game *g)
{
	this->game = g;
	this->sessions = new std::vector<Session*>;
	this->server = new QTcpServer(this); // Creates a server
	this->server->listen(QHostAddress::Any, 2049);
	connect(this->server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
	std::cout << "[Server] Network intialised" << std::endl;
	localAlreadyConnected = false;
}

Network::~Network()
{

}


void Network::onNewConnection() {
	std::cout << "[Server] New connection received" << std::endl;
	QTcpSocket* socket = this->server->nextPendingConnection(); // Gets a socket from the last pending connection

	Player * p;

	if(!localAlreadyConnected) {
		std::cout << "Getting the localplayer for that first session" << std::endl;
		localAlreadyConnected = true;
		p = this->game->getLocalPlayer();
		std::cout << p << std::endl;
	} else {
		p = this->game->getNonLocalPlayer();
		std::cout << "non localplayer taken" << std::endl;
	}

	Session* session = new Session(p, this->game, socket, this->sessions);
	connect(socket, SIGNAL(readyRead()), session, SLOT(onData())); // Calls onData() in this socket when readyRead() is called in socket
	std::cout << "[Server] ip from new connection is " << socket->IPv4Protocol << std::endl;
	this->sessions->push_back(session); // new Player is just a test!
}
