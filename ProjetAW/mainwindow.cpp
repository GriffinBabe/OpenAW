#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPainter>
#include <QGraphicsScene>
#include <QResource>

int MainWindow::cellDim = 32; //static int value of square cells dimension! important!

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	QResource::registerResource("resources.qrc"); //Resources list
	setFixedSize(size());
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

void MainWindow::resize() {
	/*
	 * Resizes the window for showing all cells width 32px quare dimension
	 */
	std::cout << "Window size is: " << size().width() << "; " << size().height() << std::endl;
	std::cout << "Cell dim is: " << cellDim << std::endl;
	int& height = size().rheight(); // Is a pointer so it can be modified later
	int& width = size().rwidth();
	height = this->game->getMap()->getSizeY()*cellDim;
	width = this->game->getMap()->getSizeX()*cellDim;

}

void MainWindow::paintEvent(QPaintEvent *event) {
	QPainter painter(this);
	painter.fillRect(10, 10, 10, 10, Qt::red);
	painter.drawPixmap(game->getCursorX()*cellDim,game->getCursorY()*cellDim,cellDim,cellDim,*cursorImage);
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
	game->setCursor(event->x(), event->y());
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
	switch(event->key()) {
		case 16777234: this->game->cursorLeft();
						break;
		case 16777235: this->game->cursorUp();
						break;
		case 16777236: this->game->cursorRight();
						break;
		case 16777237: this->game->cursorDown();
						break;
	}
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
	this->game->setCellDim(cellDim); // Set the cell dimension value to game, is usefull for controller method in game
	resize();
	std::cout << "Game Set in View/Controller" << std::endl;
	gameSet = true;
}
