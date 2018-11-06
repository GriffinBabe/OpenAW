#include "networkclient.h"
#include <iostream>

NetworkClient::NetworkClient(Game* g, std::string ip)
{
	std::cout << "[Client] Client initialised" << std::endl;
	this->socket = new QTcpSocket();
	connect(this->socket, SIGNAL(connected()), this, SLOT(this.onConnected())); // connects the SIGNAL connected() to the slot onConnected()
	this->socket->connectToHost(QString::fromStdString(ip), 2049);

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
	QByteArray data =
}

void NetworkClient::onDisconnected()
{
	std::cout << "[Client] Disconnected" << std::endl;
}

