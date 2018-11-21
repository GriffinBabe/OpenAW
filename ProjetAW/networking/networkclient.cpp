#include "networkclient.h"
#include <iostream>

NetworkClient::NetworkClient(Game* g, std::string ip)
{
	this->socket = new QTcpSocket();
	connect(this->socket, SIGNAL(connected()), this, SLOT(onConnected())); // connects the SIGNAL connected() to the slot onConnected()
	this->socket->connectToHost(QString::fromStdString(ip), 2049); // connects to the server
}

NetworkClient::~NetworkClient()
{

}

void NetworkClient::onConnected()
{
	std::cout << "[Client] Connected to server" << std::endl;
	connect(this->socket, SIGNAL(disconnected()), this, SLOT(onDisconnected())); // Calls onDisconnected() when disconnected() gets called
	connect(this->socket, SIGNAL(readyRead()), this, SLOT(onData())); // Calls onData() when readyRead() gets called
}

void NetworkClient::onData()
{
	std::cout << "[Client] Receiving data" << std::endl;
}

void NetworkClient::onDisconnected()
{
	std::cout << "[Client] Disconnected" << std::endl;
}

