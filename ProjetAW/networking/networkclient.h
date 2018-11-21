#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include "game.h"
#include <QTcpSocket>

class NetworkClient : public QObject // To use signals, slots
{
	Q_OBJECT
public:
	NetworkClient(Game* g, std::string ip);
	virtual ~NetworkClient();

	void sendJson(QJsonObject obj);

public slots:
	void onConnected();
	void onData();
	void onDisconnected();

private:
	Game* game;
	bool suicide_pill;
	QTcpSocket* socket;

	int currentSize;
	bool isConfigured;
};

#endif // NETWORKCLIENT_H
