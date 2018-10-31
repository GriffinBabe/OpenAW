#include "ui.h"
#include <iostream>
#include <vector>
#include <QString>

UI::UI()
{
	this->arrow = new QPixmap(":/Images/arrow.png");
	this->moveCellImage = new QPixmap(":/Images/Terrain/moveCell.png");
	this->target = new QPixmap(":/Images/target.png");
	this->redtarget = new QPixmap(":/Images/redtarget.png");
	this->menuBoxes = new std::vector<MenuBox*>();
	this->attackableUnits = new std::vector<Unit*>();
	this->selectedBox = nullptr;
	this->selectedAttackableUnit = nullptr;
	menuType = 0;
}

/*
 * This method paints the mapMenu, that can let you end the turn, for exemple.
 */
void UI::mapMenu(QPainter* p) {
	p->fillRect(this->selectedBox->getPosX()-10, this->selectedBox->getPosY()-10,
				this->selectedBox->getWidth()+10, this->selectedBox->getHeight()+10, Qt::red);
	for (MenuBox* box : *this->menuBoxes) {
		p->drawPixmap(box->getPosX(), box->getPosY(), box->getWidth(), box->getHeight(), *box->getImage());
	}
}

/*
 * This method enlightend all the cells where this unit can move
 */
void UI::moveMenu(QPainter* p, Unit* u) {
	std::vector<std::pair<int,int>>::iterator it;
	for (it = moveCells.begin(); it != moveCells.end(); ++it) {
		p->drawPixmap((*it).first*cellDim,(*it).second*cellDim,
					  cellDim, cellDim, *this->moveCellImage);
	}

}

/*
 * This menu shows the possibility of a unit, or a building
 */
void UI::unitMenu(QPainter* p) {
	p->fillRect(this->selectedBox->getPosX()-10, this->selectedBox->getPosY()-10,
				this->selectedBox->getWidth()+10, this->selectedBox->getHeight()+10, Qt::red);
	for (MenuBox* box : *this->menuBoxes) {
		p->drawPixmap(box->getPosX(), box->getPosY(), box->getWidth(), box->getHeight(), *box->getImage());
	}
}

/*
 * This menu puts a target on every attackablue unit
 */
void UI::attackMenu(QPainter *p, Unit *u)
{
	for (Unit* u : *this->attackableUnits) {
		if (u==this->selectedAttackableUnit) {
			p->drawPixmap(u->getPosX()*cellDim,u->getPosY()*cellDim,cellDim,cellDim,*this->redtarget);
		} else {
			p->drawPixmap(u->getPosX()*cellDim,u->getPosY()*cellDim,cellDim,cellDim,*this->target);
		}
	}

}

void UI::paint(QPainter *p, Unit *u, Buildings* b)
{
	p->setPen(Qt::black);
	if (menuType == 0) {
		return; //nothing to paint here
	} else if (menuType == 1) { //move menu
		moveMenu(p,u);
	} else if (menuType == 2 || menuType == 5) { //unit or factory menu
		unitMenu(p);
	} else if (menuType == 4) { //attack menu
		attackMenu(p,u);
	} else if (menuType == 3) {
		mapMenu(p);
	}
}

void UI::setType(Unit* u, int t)
{
	cursorPos = 0;
	clearMenuBoxes();
	menuType = t;
	int swidth = cellDim*3;
	int sheight = cellDim;
	if (this->game->getPlayerwhoplays() != this->game->getLocalPlayer()) {
		menuType = 0;
		return;
	}
	if (menuType == 1) {
		this->moveCells = this->game->getMoveCells(u);
	}
	else if (menuType == 2) {//Unit menu
		if (u->getCanAttack()) {
			this->menuBoxes->push_back(new AttackBox((width/2)-(swidth/2),(height/2)-(sheight*1.5),swidth,sheight));
		}
		Buildings* build = this->game->getBuildingOnPos(u->getPosX(), u->getPosY()); // !! MIGHT BE NULLPTR
		if (build != nullptr) {
			if (this->game->canCapture(build)) {
				this->menuBoxes->push_back(new CaptureBox((width/2)-(swidth/2),
														  (height/2),
														  swidth, sheight));
			}
		}
		this->menuBoxes->push_back(new WaitBox((width/2)-(swidth/2), (height/2)+(sheight*1.5), swidth, sheight));
		this->selectedBox = this->menuBoxes->at(0);
	} else if (menuType == 4) { // Attack menu
		/* Attack menu */
		this->attackableUnits = this->game->getAttackableUnits(u);
		if (this->attackableUnits->size() > 0) {
			this->selectedAttackableUnit = this->attackableUnits->at(0);
		} else {
			setType(u, 0); // The attackable units list is empty, we set the ui to no menu
		}
	} else if (menuType == 3) { //map menu
		this->menuBoxes->push_back(new NextTurnBox((width/2)-(swidth/2),
												   (height/2),
												   swidth, sheight));
		this->menuBoxes->push_back(new WaitBox((width/2)-(swidth/2), (height/2)+(sheight*1.5), swidth, sheight));
		this->selectedBox = this->menuBoxes->at(0);
	}
}



void UI::setType(Buildings *f, int t)
{
	cursorPos = 0;
	clearMenuBoxes();
	menuType = t;
	int swidth = cellDim*3;
	int sheight = cellDim;
	if (this->game->getPlayerwhoplays() != this->game->getLocalPlayer()) {
		menuType = 0;
		return;
	}
	if (menuType == 5) { // Factory Menu
		if (this->game->canBuildFactory(dynamic_cast<FactoryBuilding*>(f),1)) { // we downcast Buildings* b to FactoryBuilding* b
			this->menuBoxes->push_back(new NewInfateryBox((width/2)-(swidth/2),(height/2)-(sheight*3),swidth,sheight));
		}
		if (this->game->canBuildFactory(dynamic_cast<FactoryBuilding*>(f),2)) {
			this->menuBoxes->push_back(new NewBazookaBox((width/2)-(swidth/2),(height/2)-(sheight*2),swidth,sheight));
		}
		if (this->game->canBuildFactory(dynamic_cast<FactoryBuilding*>(f),3)) {
			this->menuBoxes->push_back(new NewReconBox((width/2)-(swidth/2),(height/2)-(sheight*1),swidth,sheight));
		}
		if (this->game->canBuildFactory(dynamic_cast<FactoryBuilding*>(f),4)) {
			this->menuBoxes->push_back(new NewAntiAirBox((width/2)-(swidth/2),(height/2),swidth,sheight));
		}
		if (this->game->canBuildFactory(dynamic_cast<FactoryBuilding*>(f),5)) {
			this->menuBoxes->push_back(new NewTankBox((width/2)-(swidth/2),(height/2)+(sheight*1),swidth,sheight));
		}
		if (this->game->canBuildFactory(dynamic_cast<FactoryBuilding*>(f),6)) {
			this->menuBoxes->push_back(new NewMdTankBox((width/2)-(swidth/2),(height/2)+(sheight*2),swidth,sheight));
		}
		if (this->game->canBuildFactory(dynamic_cast<FactoryBuilding*>(f),7)) {
			this->menuBoxes->push_back(new NewMegaTankBox((width/2)-(swidth/2),(height/2)+(sheight*3),swidth,sheight));
		}
		if (this->game->canBuildFactory(dynamic_cast<FactoryBuilding*>(f),8)) {
			this->menuBoxes->push_back(new NewNeoTankBox((width/2)-(swidth/2),(height/2)+(sheight*4),swidth,sheight));
		}
		this->menuBoxes->push_back(new WaitBox((width/2)-(swidth/2),(height/2)+(sheight*5),swidth,sheight));
		this->selectedBox = this->menuBoxes->at(0);
	}
}


void UI::setDimensions(int w, int h, int c) {
	width = w;
	cellDim = c;
	height = h;
}

void UI::setGame(Game *g)
{
	this->game = g;
}

void UI::setMoveCells(std::vector<std::pair<int, int> > mv)
{
	this->moveCells = mv;
}

int UI::getType()
{
	return this->menuType;
}

void UI::clearMenuBoxes()
{
	cursorPos = 0;
	delete(this->menuBoxes);
	this->menuBoxes = new std::vector<MenuBox*>();
}

MenuBox *UI::getSelectedBox()
{
	return this->selectedBox;
}

Unit *UI::getSelectedAttackableUnit()
{
	return this->selectedAttackableUnit;
}

void UI::cursorDown() {
	int newPos = cursorPos;
	if (menuType == 2 || menuType == 3 || menuType == 5) {
		if (++newPos < this->menuBoxes->size()) { // Unit menu has only two options (for the moment): attack and wait
			cursorPos++;
			this->selectedBox = this->menuBoxes->at(cursorPos);
		}
	} else if (menuType ==4) {
		if (++newPos < this->attackableUnits->size()) {
			cursorPos++;
			this->selectedAttackableUnit = this->attackableUnits->at(cursorPos);
		}
	}
}

void UI::cursorUp() {
	int newPos = cursorPos;
	if (--newPos >= 0) {
		cursorPos--;
		if (menuType == 2 || menuType == 3 || menuType == 5) {
			this->selectedBox = this->menuBoxes->at(cursorPos);
		} else if (menuType == 4) {
			if (this->attackableUnits->size() > 0) {
				this->selectedAttackableUnit = this->attackableUnits->at(cursorPos);
			}
		}
	}
}
