#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include "game.h"
#include <QTcpSocket>

class Session : public QObject // Uses SIGNAL, SLOTS
{
	Q_OBJECT
public:
	Session(Player* p, Game* g, QTcpSocket* s, std::vector<Session*>* sess);
	virtual ~Session();
	void sendJson(QJsonObject obj); // Sends a message
	void sendAllButThisJson(QJsonObject obj);

public slots:
	void onData();
	void onDisconnection();

private:
	Player* player;
	Game* game;
	QTcpSocket* socket;
	std::vector<Session*>* sessions;


	int currentSize;

	void parseRequest();
	void configure();
};
#endif // SESSION_H
