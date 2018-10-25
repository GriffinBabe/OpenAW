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
	ImageHolder holder; // Class that contains all image files into PixMap*
	QResource::registerResource("resources.qrc"); //Resources list
	setMouseTracking(true); // Enables mouse movement event
	gameSet = false;
	ui->setupUi(this);
	frameCount = 0;
	connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
	timer.start(16);
}

MainWindow::~MainWindow()
{
	delete ui;
}

void MainWindow::resize() {
	/*
	 * Resizes the window for showing all cells width 32px quare dimension
	 */
	int height = size().height(); // Is a pointer so it can be modified later
	int width = size().width();
	height = this->game->getMap()->getSizeY()*cellDim;
	width = this->game->getMap()->getSizeX()*cellDim;
	setFixedHeight(height);
	setFixedWidth(width);
}

void MainWindow::paintEvent(QPaintEvent *event) {
	QPainter painter(this);

	//Draws grass everywhere
	for (int x = 0; x < this->game->getMap()->getSizeX(); x++) {
		for (int y = 0; y < this->game->getMap()->getSizeY(); y++) {
			painter.drawPixmap(x*cellDim,y*cellDim,cellDim,cellDim,*holder.getGrassImage());
		}
	}
	//Draws the map
	for (int x = 0; x < this->game->getMap()->getSizeX(); x++) {
		for (int y = 0; y < this->game->getMap()->getSizeY(); y++) {
			int type = game->getMap()->getCellAt(x, y).gettype();
			painter.drawPixmap(x*cellDim,y*cellDim,cellDim,cellDim,*holder.getTerrainImage(type));
		}
	}
	//Draws Buildings


	//Draws ground unit
	std::vector<Unit*> units = *this->game->getUnits();
	std::vector<Unit*>::iterator it;
	for (it = units.begin(); it != units.end(); ++it) {
		(*it)->getOwner()->get
	}


	//Draws air unit


	//Draws UI

	//Draws the cursor
	painter.drawPixmap(game->getCursorX()*cellDim,game->getCursorY()*cellDim,cellDim,cellDim,*holder.getCursorImage());
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
	game->setCursor(event->x(), event->y());
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
	std::cout << event->key() << std::endl;
	switch(event->key()) {
		case 16777234: this->game->cursorLeft(); // Left arrow
						break;
		case 16777235: this->game->cursorUp(); // Up arrow
						break;
		case 16777236: this->game->cursorRight(); // Right arrow
						break;
		case 16777237: this->game->cursorDown(); // Down arrow
						break;
		case 16777220: this->game->selectElement(); // select element on cursor, can be a cell, an unit or a building
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
