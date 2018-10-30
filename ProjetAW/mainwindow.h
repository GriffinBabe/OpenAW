#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QImage>
#include <QTimer>
#include "game.h"
#include "imageholder.h"
#include "ui.h"

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
	QTimer timer;
	void resize();
	int gcd(int a, int b); // Greatest common divisor, used for cell size

	UI* menu;
	Game* game;
	ImageHolder holder;
	bool gameSet;
	int frameCount;
	static int cellDim;

	int cursorX, cursorY;
	Unit* selectedUnit;
	FactoryBuilding* selectedFactory;
	void cursorUp();
	void cursorDown();
	void cursorLeft();
	void cursorRight();
	void setCursor(int x, int y);
	void selectElement();
	void noSelectedElement();

	bool moveMode; //When selecting a move cell for unit
	bool unitMode; //
	void action(int id);
};

#endif // MAINWINDOW_H
