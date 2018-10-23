#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPainter>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	gameSet = false;
	ui->setupUi(this);
	frameCount = 0;
	connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
	timer.start(16);
	image = QImage("cara_pils.jpg");
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	painter.fillRect(10, 10, 10, 10, Qt::red);
	painter.drawImage(10, 10, this->image);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
	std::cout << event->x() << event->y() << std::endl;
}

void MainWindow::keyPressEvent(QKeyEvent *event) {
	std::cout << event->key() << std::endl;
}

void MainWindow::tick() {
	frameCount++;
	update();
}

void MainWindow::setGame(Game *game)
{
	this->game = game;
	std::cout << "Game Set in View/Controller" << std::endl;
	gameSet = true;
}


