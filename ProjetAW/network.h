#ifndef SERVER_H
#define SERVER_H

#include "QTcpServer"
#include "QThread"
#include "game.h"

class Network : public QThread // Server is a thrad
{
public:
	Network(Game* g);
	virtual ~Network();

public slots:
	void onNewConnection();

signals: // Used to communicate with other threads

protected:
	void run();

private:
	QTcpServer* server;
	std::vector<Session*>* sessions;
	Game* game;
	bool suicide_pill; // If suicide_pill is on, the run loop will stop
};

// ---------------------------------------------------------------------------------------------------------

class Session : public QThread
{
public:
	Session(Player* p, Game* g, QTcpSocket* s);

protected:
	void run();

private:
	Player* player;
	Game* game;
	QTcpServer* socket;
};


// ---------------------------------------------------------------------------------------------------------

class NetworkClient : public QThread
{
public:
	NetworkClient(Game* g, std::string ip);

public slots:
	void onNewConnection();

signals: // Used to communicate with other threads

protected:
	void run();

private:
	Game* game;
	bool suicide_pill;
	QTcpSocket* socket;
};

#endif // SERVER_H
