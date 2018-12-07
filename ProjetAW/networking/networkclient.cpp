#include "networkclient.h"
#include <iostream>
#include <QJsonDocument>
#include <QJsonObject>
#include <QDataStream>
#include <QByteArray>
#include <QJsonArray>

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
		newOwner1->setCountry(5); // The country for the blue player is 5
		Player* newOwner2 = this->game->getPlayerByTeamcolor('R'); // The country for the red player is 10
		newOwner2->setCountry(10);

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

		foreach (const QJsonValue & v, json["units"].toArray()) {
			Player* owner = this->game->getPlayerByCountry(v.toObject().value("country").toInt());
			int x = v.toObject().value("x").toInt();
			int y = v.toObject().value("y").toInt();
			int id = v.toObject().value("type").toInt();
			this->game->createUnit(owner, x, y, id);
		}

		isConfigured = true;
	} else { // if it is configured
		if (json.contains(QString("move"))) {
			int unitX = json["move"].toArray().at(0).toInt();
			int unitY = json["move"].toArray().at(1).toInt();
			int newX = json["move"].toArray().at(2).toInt();
			int newY = json["move"].toArray().at(3).toInt();
			Unit* u = this->game->getUnitOnPos(unitX, unitY);
			this->game->moveUnit(u, std::pair<int,int>(newX, newY));
			if (json.contains(QString("attack"))) {
				int attackX = json["attack"].toArray().at(0).toInt();
				int attackY = json["attack"].toArray().at(1).toInt();
				this->game->attack(u, this->game->getUnitOnPos(attackX, attackY), true);
			} else if (json.contains(QString("capture"))) {
				if (json["capture"].toBool()) {
					this->game->capture(this->game->getBuildingOnPos(u->getPosX(), u ->getPosY()));
				}
			}
		} else if (json.contains(QString("build"))) {
			int x = json["build"].toArray().at(0).toInt();
			int y = json["build"].toArray().at(1).toInt();
			QString type = json["type"].toString();
			int id = this->game->getUnitIDbyName(type.toStdString());
			Buildings* b = this->game->getBuildingOnPos(x, y);
			Player* ow = b->getOwner();
			this->game->createUnit(b, ow, id);
		} else if (json.contains(QString("endofturn"))) {
			if (json["endofturn"].toBool()) {
				this->game->nextTurn();
			}
		}
	}
}

void NetworkClient::onDisconnected()
{
	std::cout << "[Client] Disconnected" << std::endl;
}


void NetworkClient::moveWait(Unit *u, int x, int y, bool fuse)
{
	QJsonObject move;
	move.insert("move", QJsonArray() << u->getPosX() << u->getPosY() << x << y);
	if (this->game->moveWillFuse(u, x, y)) {
		move.insert("join", true);
	}
	sendJson(move);
}

void NetworkClient::moveAttack(Unit *u, int x, int y, int ax, int ay)
{
	QJsonObject obj;
	obj.insert("move", QJsonArray() << u->getPosX() << u->getPosY() << x << y);
	obj.insert("attack", QJsonArray() << ax << ay);
	if (this->game->moveWillFuse(u, x, y)) {
		obj.insert("join", true);
	}
	sendJson(obj);
}

void NetworkClient::moveCapture(Unit *u, int x, int y)
{
	QJsonObject obj;
	obj.insert("move", QJsonArray() << u->getPosX() << u->getPosY() << x << y);
	if (this->game->moveWillFuse(u, x, y)) {
		obj.insert("join", true);
	}
	obj.insert("capture", true);
	sendJson(obj);
}

void NetworkClient::endOfTurn()
{
	QJsonObject obj;
	obj.insert("endofturn", true);
	sendJson(obj);
}

void NetworkClient::build(Buildings* b, int id) {
	QJsonObject obj;
	obj.insert("build", QJsonArray() << b->getPosX() << b->getPosY());
	obj.insert("type", QString::fromStdString(this->game->getUnitNamebyID(id)));
	sendJson(obj);
}

