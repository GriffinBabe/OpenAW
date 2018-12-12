#include "session.h"
#include <iostream>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QDataStream>
#include <QJsonArray>

Session::Session(Player* p, Game* g, QTcpSocket* s,std::vector<Session*>* sess) {
	this->player = p;
	this->game = g;
	this->socket = s;
	this->sessions = sess;

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
	std::cout << "[Server" << this->player->getUsername() << "'s Session] Data Size is: " << (quint32) data.length() << std::endl;

	this->socket->write(data);
	std::cout << "[Server " << this->player->getUsername() << "'s session] Sending " << data.toStdString() << std::endl;
}

void Session::sendAllButThisJson(QJsonObject obj)
{
	for (Session* s : *this->sessions) {
		if (s!=this) {
			s->sendJson(obj);
		}
	}
}


void Session::onData()
{
	std::cout << "[Server Session] Received data from client " << this->player->getUsername() << std::endl;
	if(currentSize == 0) {
		if(this->socket->bytesAvailable() < 4) {
			return;
		}
		QDataStream in(this->socket);
		in >> currentSize;
	}
	if(this->socket->bytesAvailable() < currentSize) {
		return;
	}
	QByteArray data = this->socket->read(currentSize);
	std::cout << data.toStdString() << std::endl;
	currentSize = 0;

	QJsonDocument doc = QJsonDocument::fromJson(data);
	QJsonObject json = doc.object();

	if (json.contains(QString("getconfig"))) {
		configure();
	} else if (json.contains(QString("move"))) {
		if (this->player != this->game->getLocalPlayer()) { // Or else action would be repeated twice
			/* We don't care about the fusing in our game as it is automatic, we just send it back if needed*/
			int unitX = json["move"].toArray().at(0).toInt();
			int unitY = json["move"].toArray().at(1).toInt();
			int newX = json["move"].toArray().at(2).toInt();
			int newY = json["move"].toArray().at(3).toInt();
			Unit* u = this->game->getUnitOnPos(unitX,unitY);
			this->game->moveUnit(u, std::pair<int,int>(newX,newY));
			if (json.contains(QString("capture"))) {
				if (json["capture"].toBool()) {
					this->game->capture(this->game->getBuildingOnPos(newX,newY));
				}
			}
			if (json.contains(QString("attack"))) {
				int x = json["attack"].toArray().at(0).toInt();
				int y = json["attack"].toArray().at(1).toInt();
				this->game->attack(u,this->game->getUnitOnPos(x,y),true);
			}
		} else if (json.contains(QString("build"))) {
			int x = json["build"].toArray().at(0).toInt();
			int y = json["build"].toArray().at(1).toInt();
			int id = this->game->getUnitIDbyName(json["type"].toString().toStdString());
			Buildings* b = this->game->getBuildingOnPos(x,y);
			this->game->createUnit(this->game->getBuildingOnPos(x,y), b->getOwner(), id);
		} else if (json.contains(QString("endofturn"))) {
			if (json["endofturn"].toBool()) {
				this->game->nextTurn();
			}
		}

	}
	this->sendAllButThisJson(json); // Confirms the thing
}

void Session::onDisconnection()
{
	std::cout << "[Server Session] Client " << this->player->getUsername() << " disconnected!" << std::endl;
}

void Session::configure()
{
	QJsonObject obj;
	obj.insert("income", this->game->getIncome());
	obj.insert("map", this->game->getMapId());
	obj.insert("firstplayer", 5);
	obj.insert("secondplayer", 10);
	obj.insert("youplay", "firstplayer");

	QJsonArray units;
	for (Unit* u : *this->game->getUnits()) {
		QJsonObject unit;
		unit.insert("country", u->getOwner()->getCountry());
		unit.insert("type", QString::fromStdString(this->game->getUnitNamebyID(u->getID())));
		unit.insert("x", u->getPosX());
		unit.insert("y", u->getPosY());
		units << unit; // Inserts the new unit in the units list
	}
	sendJson(obj);
}
