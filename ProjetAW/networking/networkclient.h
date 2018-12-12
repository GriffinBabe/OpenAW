#ifndef NETWORKCLIENT_H
#define NETWORKCLIENT_H

#include "game.h"
#include <QTcpSocket>

class MainWindow;

class NetworkClient : public QObject // To use signals, slots
{
	Q_OBJECT
public:
	NetworkClient(Game* g, std::string ip, MainWindow* w);
	virtual ~NetworkClient();

	void sendJson(QJsonObject obj);

	void moveWait(Unit* u, int oldX, int oldY, int x, int y, bool fuse);
	void moveAttack(Unit* u, int oldX, int oldY, int x, int y, int ax, int ay);
	void moveCapture(Unit* u, int oldX, int oldY, int x, int y);
	void build(Buildings* b, int id);
	void endOfTurn();
	bool getConfigured();

public slots:
	void onConnected();
	void onData();
	void onDisconnected();

private:
	Game* game;
	bool suicide_pill;
	MainWindow* mw;
	QTcpSocket* socket;

	int currentSize = 0;
	bool isConfigured;

	void askConfiguration();
};

#endif // NETWORKCLIENT_H
