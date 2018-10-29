#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPainter>
#include <QGraphicsScene>
#include <QResource>
#include <QPixmap>

int MainWindow::cellDim = 64; //static int value of square cells dimension! important!

MainWindow::MainWindow(QWidget *parent) :
	QMainWindow(parent),
	ui(new Ui::MainWindow)
{
	setWindowIcon(QIcon(":/Images/Icon/icone.png"));
	this->menu = new UI();
	ImageHolder holder; // Class that contains all image files into PixMap*
	QResource::registerResource("resources.qrc"); //Resources list
	setMouseTracking(true); // Enables mouse movement event
	gameSet = false;
	ui->setupUi(this);
	frameCount = 0;
	connect(&timer, SIGNAL(timeout()), this, SLOT(tick()));
	timer.start(16);
	cursorX = 0;
	cursorY = 0;
	selectedUnit = NULL;
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
	this->menu->setDimensions(size().width(), size().height(), cellDim);
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
    std::vector<Buildings*> buildings= *this->game->getBuildings();
    std::vector<Buildings*>::iterator at;
    for (at = buildings.begin(); at != buildings.end(); ++at) {
		char teamColor = 'N'; // N for neutral
		if ((*at)->getOwner() != nullptr) {
			teamColor = (*at)->getOwner()->getTeamColor();
		}
        painter.drawPixmap((*at)->getPosX() * cellDim,
						   ((*at)->getPosY()-1) * cellDim,
                           cellDim,
						   cellDim*2,
						   *holder.getBuildingImage((*at)->getID(),teamColor));
    }


	//Draws ground unit
	std::vector<Unit*> units = *this->game->getUnits();
	std::vector<Unit*>::iterator it;
	for (it = units.begin(); it != units.end(); ++it) {
		painter.drawPixmap((*it)->getPosX() * cellDim,
						   (*it)->getPosY() * cellDim,
						   cellDim,
						   cellDim,
						   *holder.getUnitImage((*it)->getID(),(*it)->getOwner()->getTeamColor()));
	}


	//Draws air unit

	//Draws the cursor
	painter.drawPixmap(cursorX*cellDim,cursorY*cellDim,cellDim,cellDim,*holder.getCursorImage());

	//Draws UI
	this->menu->paint(&painter,this->selectedUnit);
	if (this->selectedUnit != nullptr) {
		if (this->selectedUnit->getCanMove()) {
			this->menu->moveMenu(&painter,this->selectedUnit);
		} else {
			this->menu->unitMenu(&painter, this->selectedUnit);
		}
	}
}

void MainWindow::mousePressEvent(QMouseEvent *event) {
	if (event->button()==1) {
		selectElement();
	}
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
	setCursor(event->x(), event->y());
}


void MainWindow::keyPressEvent(QKeyEvent *event) {
	switch(event->key()) {
		case 16777234: cursorLeft(); // Left arrow
						break;
		case 16777235: cursorUp(); // Up arrow
						break;
		case 16777236: cursorRight(); // Right arrow
						break;
		case 16777237: cursorDown(); // Down arrow
						break;
		case 16777220: selectElement(); //Enter, select element on cursor, can be a cell, an unit or a building
						break;
		case 16777216: noSelectedElement(); //Escape, quits any menu
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
	this->menu->setGame(game);
	resize();
	std::cout << "Game Set in View/Controller" << std::endl;
	gameSet = true;
}

void MainWindow::selectElement()
/*
 *  This method selects the unit, building and cell where the cursor is.
 *  There is a priority to be respect and it's ruled by the return statement.
 */
{
	//Checks if there is any unit on it and selects it
	if (this->game->checkUnitOnPos(cursorX,cursorY)) { //We know that there is a unit
		if (this->game->getUnitOnPos(cursorX, cursorY)->getOwner() == this->game->getLocalPlayer()) {
			this->selectedUnit = this->game->getUnitOnPos(cursorX, cursorY); //The selectedPointer unit is now set
			if (this->selectedUnit->getCanMove()) {
				this->menu->setMoveCells(this->game->getMoveCells(this->selectedUnit)); //Sets the cells where the unit can move in the UI class
			}
			return;
		}
	}

	if (this->selectedUnit != nullptr) { // We have a selected player
		if (this->selectedUnit->getCanMove()) {//The unit hasn't mooved yet
			this->game->moveUnit(this->selectedUnit,std::pair<int,int>(cursorX,cursorY));
			// The unit will move if the game tells it's possible
		}
	}
}

void MainWindow::noSelectedElement()
{
	this->selectedUnit = nullptr;
}

void MainWindow::setCursor(int x, int y)
/*
 * set cursor to target cell the parameters are mouse
 */
{
	cursorX = x/cellDim;
	cursorY = y/cellDim;
}

void MainWindow::cursorDown() {
	if (this->selectedUnit != nullptr) {
		if (this->selectedUnit->getCanAttack()) {
			this->menu->cursorDown();
		}
	}
	int temp = cursorY + 1;
	if (temp <= this->game->getMap()->getSizeY()) { // First put ++ before variable else the condition check will be false
		cursorY++;
	}
}

void MainWindow::cursorLeft() {
	int temp = cursorX - 1;
	if (temp >= 0) {
		cursorX--;
	}
}

void MainWindow::cursorRight() {
	int temp = cursorX + 1;
	if (temp <= this->game->getMap()->getSizeX()) {
		cursorX++;
	}
}

void MainWindow::cursorUp() {
	if (this->selectedUnit != nullptr) {
		if (this->selectedUnit->getCanAttack()) {
			this->menu->cursorUp();
		}
	}
	int temp = cursorY - 1;
	if (temp >= 0) {
		cursorY--;
	}
}
