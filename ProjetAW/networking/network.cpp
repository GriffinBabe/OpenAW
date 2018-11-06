#include "network.h"
#include <iostream>
#include "QTcpSocket"

Network::Network(Game *g)
{
	this->game = g;
	this->server = new QTcpServer(); // Creates a server
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

		/* Now that we have a socket to communicate with the new client, we are going to ask him his player informations

		// this->sessions(new Session(,this->game,socket));
	}
}*/

void Network::onNewConnection()
{
	std::cout << "[Server] new connection received" << std::endl;
}
