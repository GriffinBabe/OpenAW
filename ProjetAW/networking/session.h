#ifndef SESSION_H
#define SESSION_H

#include <QObject>
#include "game.h"
#include <QTcpSocket>

class Session : public QObject // Uses SIGNAL, SLOTS
{
	Q_OBJECT
public:
	Session(Player* p, Game* g, QTcpSocket* s);
	virtual ~Session();
	void send(); // Sends a message

public slots:
	void onData();
	void onDisconnection();

private:
	Player* player;
	Game* game;
	QTcpSocket* socket;

	void parseRequest();
};
#endif // SESSION_H
