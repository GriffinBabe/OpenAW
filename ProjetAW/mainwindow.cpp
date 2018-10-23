#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPainter>
#include <QGraphicsScene>
#include <QResource>

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	QResource::registerResource("resources.qrc"); //Resources list
	setMouseTracking(true); // Enables mouse movement event
	gameSet = false;
	ui->setupUi(this);
	frameCount = 0;
	connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
	timer.start(16);
	this->cursorImage = new QPixmap(":/Images/cursor.png"); // Imports cursor image
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	painter.fillRect(10, 10, 10, 10, Qt::red);
	painter.drawPixmap(game->getCursorX()*64,game->getCursorY()*64,64,64,*cursorImage);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
	game->setCursor(event->x(), event->y());
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
	std::cout << event->key() << std::endl;
}

void MainWindow::tick() {
	if (gameSet) {
		frameCount++;
		update(); // calls paintEvent
	}
}

void MainWindow::setGame(Game *game)
{
	this->game = game;
	std::cout << "Game Set in View/Controller" << std::endl;
	gameSet = true;
}
