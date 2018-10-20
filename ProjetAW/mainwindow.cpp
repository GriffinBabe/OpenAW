#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include <QImage>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QEvent>
#include <QDebug>
#include <iostream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
	frameCount = 0;
	gameSetted = false;
	connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
	timer.start(16); // ~60 FPS refresh rate
	image= QImage("cara_pils.jpg");
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event)
{
	QPainter painter(this);
	painter.fillRect(10,10, 10, 10, Qt::red);
	painter.drawImage(10, 10, this->image);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
	std::cout << event->x() << "," << event->y() << std::endl;
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
	qDebug() << event->key();
}

void MainWindow::tick()
{
	if (gameSetted) {
		frameCount++;
		update(); // calls paintEvent
	}
}

void MainWindow::setGame(Game& game) {
	this->game = &game;
	gameSetted = true; // Used so we can start showing stuff
}
