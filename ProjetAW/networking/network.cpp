#include "network.h"
#include <iostream>
#include "QTcpSocket"

Network::Network(Game *g)
{
	this->game = g;
	this->sessions = new std::vector<Session*>;
	this->server = new QTcpServer(); // Creates a server
	connect(this->server, SIGNAL(newConnection()), this, SLOT(onNewConnection()));
	std::cout << "[Server] Network intialised" << std::endl;
}

Network::~Network()
{

}

/*
void Network::run()
{
	while (true) { // Will always run until we say so
		if (suicide_pill) {
			break;
		}
		server->listen(QHostAddress::Any, 2049); // 2049 is the communication port
		std::cout << "I am the server" << std::endl;
		QTcpSocket* socket = new QTcpSocket();
		connect(socket, SIGNAL(newConnection()), this, SLOT(onNewConnection())); // Logs the socket to the server

		Now that we have a socket to communicate with the new client, we are going to ask him his player informations

		// this->sessions(new Session(,this->game,socket));
	}
}*/

void Network::onNewConnection() {
	std::cout << "[Server] new connection received" << std::endl;
	QTcpSocket* socket = this->server->nextPendingConnection(); // Gets a socket from the last pending connection


	Session* session = new Session(new Player("test", 'T'), this->game, socket);
	connect(socket, SIGNAL(readyRead()), session, SLOT(session.onData())); // Calls onData() in this socket when readyRead() is called in socket
	std::cout << "[Server] ip from new connection is " << socket->IPv4Protocol << std::endl;
	this->sessions->push_back(session); // new Player is just a test!
}
