#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QImage>
#include <QTimer>
#include "game.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
	Q_OBJECT

public:
	explicit MainWindow(QWidget *parent = nullptr);
	~MainWindow();
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);

	void setGame(Game* game);

public slots:
	void tick();

private:
	Ui::MainWindow *ui;
	QImage image;
	QTimer timer;

	Game* game;
	bool gameSet;
	int frameCount;
};

#endif // MAINWINDOW_H
