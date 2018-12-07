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
	this->server->waitForNewConnection();
	std::cout << "[Server] Network intialised" << std::endl;
}

Network::~Network()
{

}


void Network::onNewConnection() {
	std::cout << "[Server] New connection received" << std::endl;
	QTcpSocket* socket = this->server->nextPendingConnection(); // Gets a socket from the last pending connection

	/* TODO: Here we are going to ask for username, stuff and give game informations */

	Session* session = new Session(new Player("test", 'T'), this->game, socket,this->sessions);
	connect(socket, SIGNAL(readyRead()), session, SLOT(onData())); // Calls onData() in this socket when readyRead() is called in socket
	std::cout << "[Server] ip from new connection is " << socket->IPv4Protocol << std::endl;
	this->sessions->push_back(session); // new Player is just a test!
}
