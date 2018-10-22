#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QEvent>
#include <QDebug>
#include <QMainWindow>
#include <QTimer>
#include "ui_mainwindow.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
		/*
		 * In this class we have the view AND the controller, the Game class is the model head,
		 * and the Server class will be there network head.
		 */
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
	void paintEvent(QPaintEvent *event);
	void mousePressEvent(QMouseEvent *event);
	void keyPressEvent(QKeyEvent *event);


public slots:
	void tick();

private:
    Ui::MainWindow *ui;
	QImage image;
	QTimer timer; // Game Loop

	bool gameSetted;
	int frameCount;
};

#endif // MAINWINDOW_H
