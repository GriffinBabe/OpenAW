#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <QPainter>
#include <QGraphicsScene>
#include <QResource>
#include <QPixmap>
#include "networking/networkclient.h"

int MainWindow::cellDim = 32; //static int value of square cells dimension! important!

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
	height = this->game->getMap()->getSizeY()*cellDim + cellDim;
	width = this->game->getMap()->getSizeX()*cellDim;
	setFixedHeight(height);
	setFixedWidth(width);
	this->menu->setDimensions(size().width(), size().height(), cellDim);
}

void MainWindow::setGameSet(bool b)
{
	gameSet = b;
}

void MainWindow::paintEvent(QPaintEvent *event) {

	if (!this->client->getConfigured()) {
		std::cout << "Not configured, returning now" << std::endl;
		return;
	}

	QPainter painter(this);
	QFont font = painter.font();
    font.setPointSize(cellDim/4);
	painter.setPen(Qt::black);
	painter.setFont(font);

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
		if (!(*it)->getCanMove() && !(*it)->getCanAttack()) {
			painter.fillRect(QRect((*it)->getPosX() * cellDim,(*it)->getPosY() * cellDim,cellDim,cellDim),QColor(0,0,0,128));
		}
		if ( (*it)->getHealth() != 10) {
			painter.fillRect((*it)->getPosX() * cellDim,
							 (*it)->getPosY() * cellDim + cellDim/2,cellDim/2,cellDim/2,Qt::white);
			painter.drawText((*it)->getPosX() * cellDim,
							 (*it)->getPosY() * cellDim + cellDim, QString::number( (*it)->getHealth() ) );
		}
	}


	//Draws air unit

	//Draws the cursor
	painter.drawPixmap(cursorX*cellDim,cursorY*cellDim,cellDim,cellDim,*holder.getCursorImage());

	//Draws UI
	if (this->selectedUnit!=nullptr) {
		if (this->selectedUnit->getCanMove()) {
			this->menu->setType(this->selectedUnit, 1);
		}
	}
	this->menu->paint(&painter,this->selectedUnit, this->selectedBuildings);

    painter.drawText(cellDim,cellDim,"Player who plays: "+
					QString::fromStdString(this->game->getPlayerwhoplays()->getUsername())
					 +" Money: "+QString::number(this->game->getPlayerwhoplays()->getMoney()));


	painter.fillRect(0,this->size().height()-cellDim,this->size().width(),cellDim,QColor(240,240,150,1));
	painter.drawRect(0,this->size().height()-cellDim,this->size().width(),cellDim);
	QFont font1;
	font1.setPixelSize(cellDim/1.5);
	if (this->game->getLocalPlayer()->getTeamColor() == 'R') {
		painter.setPen(Qt::red);
	} else {
		painter.setPen(Qt::blue);
	}
	painter.setFont(font1);
	painter.drawText(cellDim,this->size().height()-cellDim/3,QString::fromStdString(this->game->getLocalPlayer()->getUsername()));
	painter.setPen(Qt::black);

	painter.drawText(this->size().width()/3,this->size().height()-cellDim/3,"|");
	painter.drawText(this->size().width()/3+cellDim,this->size().height()-cellDim/3,"Money: "+QString::number(this->game->getLocalPlayer()->getMoney()));

	painter.drawText(2*this->size().width()/3,this->size().height()-cellDim/3,"|");
	painter.drawText(2*this->size().width()/3+cellDim,this->size().height()-cellDim/3,"C: "+QString::number(this->game->getPlayerCityCount(this->game->getLocalPlayer())));

	painter.drawText(5*this->size().width()/6,this->size().height()-cellDim/3,"|");
	painter.drawText(5*this->size().width()/6+cellDim,this->size().height()-cellDim/3,"U: "+QString::number(this->game->getPlayerUnitCount(this->game->getLocalPlayer())));



}

void MainWindow::mousePressEvent(QMouseEvent *event) {
	if (event->button()==1) {
		selectElement();
	} else if (event->button()==2) {
		noSelectedElement();
	} else if (event->button()==4) {
		selectElement();
	}
}

void MainWindow::mouseMoveEvent(QMouseEvent *event) {
	setCursor(event->x(), event->y());
}

void MainWindow::wheelEvent(QWheelEvent *event)
{
	if (event->delta() > 0) { // scroll up
		this->cursorUp();
	} else if (event->delta() < 0) { // scroll down
		this->cursorDown();
	}
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

void MainWindow::setGame(Game *game, std::string ip)
{
	this->game = game;
	this->client = new NetworkClient(this->game, ip, this);
	if (this->game->getLocalPlayer()->getIA() != nullptr) {
		this->game->getLocalPlayer()->getIA()->setClient(this->client);
	}
	std::cout << "NetworkClient initialization finished." << std::endl;
}

void MainWindow::setGame2()
{
	this->menu->setGame(this->game);
	resize();
	std::cout << "Game set in view/controller" << std::endl;
	gameSet = true;
}

UI* MainWindow::getMenu()
{
	return this->menu;
}

void MainWindow::selectElement()
/*
 *  This method selects the unit, building and cell where the cursor is.
 *  There is a priority to be respect and it's ruled by the return statement.
 */
{
	if (menu->getType() == 0) { // No menu
		if (this->game->checkUnitOnPos(cursorX, cursorY)) {
			Unit* u = this->game->getUnitOnPos(cursorX, cursorY);
			if (u->getOwner() == this->game->getLocalPlayer()) {
				if (u->getCanMove()) {
					this->selectedUnit = u;
					this->menu->setType(this->selectedUnit, 1); //Move menu
					return;
				} else if (u->getCanAttack()) {
					this->selectedUnit = u;
					this->menu->setType(this->selectedUnit, 2); //Unit menu
					return;
				}
			}
		}
		if (this->game->checkBuildingOnPos(cursorX, cursorY)) {
			Buildings* b = this->game->getBuildingOnPos(cursorX,cursorY);
			if (b->getOwner()==this->game->getLocalPlayer()) {
				if (b->getID() == 1 || b->getID() == 3) { // FactoryBuilding or AirportBuilding
					this->selectedBuildings = b; // This is a downcast
					this->menu->setType(b, 5); // We set a Factory Menu
					return;
				}
			} else {
				this->menu->setType(this->selectedUnit,0);
				return;
			}
		} else {
			this->menu->setType(this->selectedUnit, 3);
			return;
		}
	}
	else if (menu->getType() == 1) { // Move menu
        if (this->game->unitCanMoveOnCell(this->selectedUnit,this->game->getMap()->getCellAt(cursorX,cursorY))) {
			this->selectedUnit->setOldPos();
			this->game->moveUnit(this->selectedUnit,std::pair<int,int>(cursorX,cursorY));
			if (std::find(this->game->getUnits()->begin(), this->game->getUnits()->end(), this->selectedUnit) != this->game->getUnits()->end()) {
				// If *this->selectedUnit is still in the vector or it has been deleted because of fusion
				this->menu->setType(this->selectedUnit, 2);
				return;
			} else {
				/* selectedUnit doesn't exists anymore*/
				this->noSelectedElement();
				return this->menu->setType(this->selectedUnit, 0); // Putain trop le swag je vais deux choses en une seule ligne
			}
		} else {
			this->menu->setType(this->selectedUnit, 0);
			this->selectedUnit = nullptr;
			return;
		}
	}
	else if (menu->getType() == 2) { // Unit menu
		this->menu->setType(this->selectedUnit, 0);
		this->action(this->menu->getSelectedBox()->getAction());
		return;
	}
	else if (menu->getType() == 3) {
		this->menu->setType(this->selectedUnit, 0);
		this->action(this->menu->getSelectedBox()->getAction());
		return;
	}
	else if (menu->getType() == 4) { // Attack Menu
		this->menu->setType(this->selectedUnit, 0);
		this->client->moveAttack(this->selectedUnit,this->selectedUnit->getOldX(), this->selectedUnit->getOldY(),this->selectedUnit->getPosX(),this->selectedUnit->getPosY(),this->menu->getSelectedAttackableUnit()->getPosX(),this->menu->getSelectedAttackableUnit()->getPosY());
		this->game->attack(this->selectedUnit,this->menu->getSelectedAttackableUnit(),true); // Game.attack(Unit* u, Unit* u2);
		return;
	}
	else if (menu->getType() == 5) { // Build Menu
		this->menu->setType(this->selectedUnit, 0);
		this->action(this->menu->getSelectedBox()->getAction());
		return;
	}

}

void MainWindow::noSelectedElement()
{
	if (this->menu->getType()==2) { // unit menu
		this->selectedUnit->setCanAttack(false);
		this->selectedUnit = nullptr;
		this->selectedBuildings = nullptr;
	} else if (this->menu->getType()==0) {
		this->selectedUnit = nullptr;
		this->selectedBuildings = nullptr;
		this->menu->setType(this->selectedUnit,3);
	} else {
		this->selectedUnit = nullptr;
		this->selectedBuildings = nullptr;
		this->menu->setType(this->selectedUnit, 0);
	}
}

void MainWindow::action(int id)
{
	if (id==2) { // capture
		this->client->moveCapture(this->selectedUnit, this->selectedUnit->getOldX(), this->selectedUnit->getOldY(), this->selectedUnit->getPosX(), this->selectedUnit->getPosY());
		this->game->capture(this->game->getBuildingOnPos(this->selectedUnit->getPosX(),this->selectedUnit->getPosY()));
		this->selectedUnit = nullptr;
		this->menu->setType(this->selectedUnit, 0);
	} else if (id==0) { // wait - do nothing
		if (this->selectedUnit != nullptr) {
			this->client->moveWait(this->selectedUnit, this->selectedUnit->getOldX(), this->selectedUnit->getOldY(), this->selectedUnit->getPosX(), this->selectedUnit->getPosY(), true);
			this->selectedUnit->setCanAttack(false); // Can't attack anymore
		}
		this->selectedUnit = nullptr;
		this->selectedBuildings = nullptr;
		this->menu->setType(this->selectedUnit, 0);
	} else if (id==1) { //attack
		this->menu->setType(this->selectedUnit, 4);
	} else if (id==3) { // pass turn
		this->client->endOfTurn();
		this->game->nextTurn();
	} else if (id==4) { // new infantery
		this->client->build(this->selectedBuildings, 1);
		this->game->createUnit(this->selectedBuildings, this->game->getLocalPlayer(), 1);
		this->selectedBuildings = nullptr;
	}
	else if (id==5) { // new Bazooka
		this->client->build(this->selectedBuildings, 2);
		this->game->createUnit(this->selectedBuildings, this->game->getLocalPlayer(), 2);
		this->selectedBuildings = nullptr;
	}
	else if (id==6) { // new recon
		this->client->build(this->selectedBuildings, 3);
		this->game->createUnit(this->selectedBuildings, this->game->getLocalPlayer(), 3);
		this->selectedBuildings = nullptr;
	}
	else if (id==7) { // new antiair
		this->client->build(this->selectedBuildings, 4);
		this->game->createUnit(this->selectedBuildings, this->game->getLocalPlayer(), 4);
		this->selectedBuildings = nullptr;
	}
	else if (id==8) { // new tank
		this->client->build(this->selectedBuildings, 5);
		this->game->createUnit(this->selectedBuildings, this->game->getLocalPlayer(), 5);
		this->selectedBuildings = nullptr;
	}
	else if (id==9) { // new mdtank
		this->client->build(this->selectedBuildings, 6);
		this->game->createUnit(this->selectedBuildings, this->game->getLocalPlayer(), 6);
		this->selectedBuildings = nullptr;
	}
	else if (id==10) { // new megatank
		this->client->build(this->selectedBuildings, 7);
		this->game->createUnit(this->selectedBuildings, this->game->getLocalPlayer(), 7);
		this->selectedBuildings = nullptr;
	}
	else if (id==11) { // new neotank
		this->client->build(this->selectedBuildings, 8);
		this->game->createUnit(this->selectedBuildings, this->game->getLocalPlayer(), 8);
		this->selectedBuildings = nullptr;
	}
	else if (id==12) { // new bcopter
		this->client->build(this->selectedBuildings, 9);
		this->game->createUnit(this->selectedBuildings, this->game->getLocalPlayer(), 9);
		this->selectedBuildings = nullptr;
	}
	else if (id==13) { // new fighter
		this->client->build(this->selectedBuildings, 10);
		this->game->createUnit(this->selectedBuildings, this->game->getLocalPlayer(), 10);
		this->selectedBuildings = nullptr;
	}
	else if (id==14) { // new bomber
		this->client->build(this->selectedBuildings, 11);
		this->game->createUnit(this->selectedBuildings, this->game->getLocalPlayer(), 11);
		this->selectedBuildings = nullptr;
	}
}

/*
 * set cursor to target cell the parameters are mouse
 */
void MainWindow::setCursor(int x, int y)
{
	cursorX = x/cellDim;
	cursorY = y/cellDim;
	if (this->menu->getType() == 2 || this->menu->getType()==3 || this->menu->getType()==4 || this->menu->getType() == 5) { // unit menu, map menu
		this->menu->moveCursor(x,y);
	}
}

void MainWindow::cursorDown() {
	if (this->menu->getType()==2 || this->menu->getType()==3 || this->menu->getType()==4 || this->menu->getType()==5) { // unit menu, map menu or attack menu
		this->menu->cursorDown();
		return;
	}
	int temp = cursorY + 1;
	if (temp <= this->game->getMap()->getSizeY()) { // First put ++ before variable else the condition check will be false
		cursorY++;
	}
}

void MainWindow::cursorLeft() {
	if (this->menu->getType()==2 || this->menu->getType()==3 || this->menu->getType()==4 || this->menu->getType()==5) { // unit menu or map menu
		this->menu->cursorUp();
		return;
	}
	int temp = cursorX - 1;
	if (temp >= 0) {
		cursorX--;
	}
}

void MainWindow::cursorRight() {
	if (this->menu->getType()==2 || this->menu->getType()==3 || this->menu->getType()==4 || this->menu->getType()==5) { // unit menu or map menu
		this->menu->cursorDown();
		return;
	}
	int temp = cursorX + 1;
	if (temp <= this->game->getMap()->getSizeX()) {
		cursorX++;
	}
}

void MainWindow::cursorUp() {
	if (this->menu->getType()==2 || this->menu->getType()==3 || this->menu->getType()==4 || this->menu->getType()==5) { // unit menu or map menu
		this->menu->cursorUp();
		return;
	}
	int temp = cursorY - 1;
	if (temp >= 0) {
		cursorY--;
	}
}
NetworkClient *MainWindow::getNetworkClient(){

    return this->client;
}
