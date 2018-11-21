#include "session.h"
#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QDataStream>

Session::Session(Player* p, Game* g, QTcpSocket* s) {
	this->player = p;
	this->game = g;
	this->socket = s;
}

Session::~Session()
{

}

/*
 * Sends a Json object through our socket, this method is the same than in networkclient
 */
void Session::sendJson(QJsonObject obj)
{
	QByteArray data = QJsonDocument(obj).toJson();
	QDataStream out(this->socket);
	out << (quint32) data.length();
	this->socket->write(data);
	std::cout << "[Server " << this->player->getUsername() << "'s session] Sending " << data.toStdString() << std::endl;
}


void Session::onData()
{
	std::cout << "[Server Session] Received data from client " << this->player->getUsername() << std::endl;
}

void Session::onDisconnection()
{
	std::cout << "[Server Session] Client " << this->player->getUsername() << " disconnected!" << std::endl;
}
