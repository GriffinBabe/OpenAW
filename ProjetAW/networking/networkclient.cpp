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


		int first = json["firstplayer"].toInt(); // We get the value of the first player
		int second = json["secondplayer"].toInt();

		std::string who = json["youplay"].toString().toStdString();

		Player* newOwner1 = this->game->getPlayerByTeamcolor('B');
		Player* newOwner2 = this->game->getPlayerByTeamcolor('R');

		if (first == 5) {
			this->game->giveBuildingsTo(newOwner1, 95);
			this->game->giveBuildingsTo(newOwner1, 92);
		} else if (first == 10) {
			this->game->giveBuildingsTo(newOwner1, 123);
			this->game->giveBuildingsTo(newOwner1, 125);
		}

		if (second == 5) {
			this->game->giveBuildingsTo(newOwner2, 95);
			this->game->giveBuildingsTo(newOwner2, 92);
		} else if (second == 10) {
			this->game->giveBuildingsTo(newOwner2, 123);
			this->game->giveBuildingsTo(newOwner2, 125);
		}

		if (who == "firstplayer") {
			this->game->setPlayerwhoplays(this->game->getPlayerByTeamcolor('B'));
		} else if (who == "secondplayer") {
			this->game->setPlayerwhoplays(this->game->getPlayerByTeamcolor('R'));
		}

		isConfigured = true;
	}
}

void NetworkClient::onDisconnected()
{
	std::cout << "[Client] Disconnected" << std::endl;
}

