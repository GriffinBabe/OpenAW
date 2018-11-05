#ifndef SERVER_H
#define SERVER_H

#include "QTcpServer"
#include "QThread"
#include "game.h"
#include "QObject"

class Session : public QObject // Uses SIGNAL, SLOTS
{
public:
	Session(Player* p, Game* g, QTcpSocket* s);
	void send(); // Sends a message

protected:
	void run();

private:
	Player* player;
	Game* game;
	QTcpSocket* socket;

	void parseRequest();
};

// -----------------------------------------------------------------------------

class Network : public QThread // Even in signals can let us deal with data, we need a thread to always listen for new connections
{
public:
	Network(Game* g);

public slots:
	void onNewConnection();
	void onData(); // When receiving some datan this method is called

private:
	QTcpServer* server;
	std::vector<Session*>* sessions;
	Game* game;
	bool suicide_pill; // If suicide_pill is on, the run loop will stop
};

// ---------------------------------------------------------------------------------------------------------

class NetworkClient : public QObject // To use signals, slots
{
public:
	NetworkClient(Game* g, std::string ip);

public slots:
	void onConnected();

private:
	Game* game;
	bool suicide_pill;
	QTcpSocket* socket;
};

#endif // SERVER_H
