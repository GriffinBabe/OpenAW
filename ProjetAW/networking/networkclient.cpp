#include "networkclient.h"
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDataStream>
#include <QByteArray>

NetworkClient::NetworkClient(Game* g, std::string ip)
{
	this->socket = new QTcpSocket();
	connect(this->socket, SIGNAL(connected()), this, SLOT(onConnected())); // connects the SIGNAL connected() to the slot onConnected()
	this->socket->connectToHost(QString::fromStdString(ip), 2049); // connects to the server
}

NetworkClient::~NetworkClient()
{

}

void NetworkClient::sendJson(QJsonObject obj)
{
	QByteArray data = QJsonDocument(obj).toJson();
	QDataStream out(this->socket);
	out << (quint32) data.length();
	this->socket->write(data);

	std::cout << "[Client] Sending " << data.toStdString() << std::endl;
}

void NetworkClient::onConnected()
{
	std::cout << "[Client] Connected to server" << std::endl;
	connect(this->socket, SIGNAL(disconnected()), this, SLOT(onDisconnected())); // Calls onDisconnected() when disconnected() gets called
	connect(this->socket, SIGNAL(readyRead()), this, SLOT(onData())); // Calls onData() when readyRead() gets called
}

void NetworkClient::onData()
{
	std::cout << "[Client] Data Received !" << std::endl;
	if(currentSize == 0) {
		if(this->socket->bytesAvailable() < 4)
			return;

		QDataStream in(this->socket);
		in >> currentSize;
	}

	if(this->socket->bytesAvailable() < currentSize)
		return;

	QByteArray data = this->socket->read(currentSize);
	std::cout << data.toStdString() << std::endl;
	currentSize = 0;

	QJsonDocument doc = QJsonDocument::fromJson(data);
	QJsonObject json = doc.object();

	/*
	 * Called on new connection to get the game informations
	 */
	if(!isConfigured) {
		this->game->setIncome((json["income"]).toInt()); // In the Json the parameter "income"
		this->game->setMap(json["map"].toInt());


		posX = json["x"].toInt();
		posY = json["y"].toInt();
		update();
		isConfigured = true;
		myTurn = true;
	} else {
		int oldX = json["oldX"].toInt();
		int oldY = json["oldY"].toInt();
		int newX = json["newX"].toInt();
		int newY = json["newY"].toInt();

		if(!(posX == oldX && posY == oldY)) {
			std::cerr << "ERROR" << std::endl;
			destroy();
			return;
		}

		posX = newX;
		posY = newY;
		myTurn = true;
		update();
	}
}

void NetworkClient::onDisconnected()
{
	std::cout << "[Client] Disconnected" << std::endl;
}

