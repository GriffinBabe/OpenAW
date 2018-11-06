#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include "game.h"
#include <QTcpSocket>

class NetworkClient : public QObject // To use signals, slots
{
	Q_OBJECT
public:
	NetworkClient(Game* g, std::string ip);

public slots:
	void onConnected();
	void onData();
	void onDisconnected();

private:
	Game* game;
	bool suicide_pill;
	QTcpSocket* socket;
};

#endif // NETWORKCLIENT_H
