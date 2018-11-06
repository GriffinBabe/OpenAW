#ifndef SERVER_H
#define SERVER_H

#include "QTcpServer"
#include "QThread"
#include "game.h"
#include "QObject"

#include "session.h"

class Network : public QThread // Even in signals can let us deal with data, we need a thread to always listen for new connections
{
	Q_OBJECT
public:
	Network(Game* g);
	virtual ~Network();

public slots:
	void onNewConnection();
	void onData(); // When receiving some datan this method is called

private:
	QTcpServer* server;
	std::vector<Session*>* sessions;
	Game* game;
	bool suicide_pill; // If suicide_pill is on, the run loop will stop
};

#endif // SERVER_H
