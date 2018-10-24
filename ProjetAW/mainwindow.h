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
	void mouseMoveEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);

	void setGame(Game* game);

public slots:
	void tick();

private:
	Ui::MainWindow *ui;
	QPixmap* cursorImage; // Image for the game cursor
	QTimer timer;
	void resize();
	int gcd(int a, int b); // Greatest common divisor, used for cell size

	Game* game;
	bool gameSet;
	int frameCount;
	static int cellDim;
};

#endif // MAINWINDOW_H
