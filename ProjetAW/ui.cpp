#include "ui.h"
#include <iostream>
#include <vector>
#include <QString>

UI::UI()
{
	this->arrow = new QPixmap(":/Images/arrow.png");
	this->moveCellImage = new QPixmap(":/Images/Terrain/moveCell.png");
	this->menuBoxes = new std::vector<MenuBox*>();
	this->selectedBox = nullptr;
	menuType = 0;
}

void UI::mapMenu(QPainter* p) {
	/*
	 * This class paints the mapMenu, that can let you end the turn, for exemple.
	 */
}

void UI::moveMenu(QPainter* p, Unit* u) {
	std::vector<std::pair<int,int>>::iterator it;
	for (it = moveCells.begin(); it != moveCells.end(); ++it) {
		p->drawPixmap((*it).first*cellDim,(*it).second*cellDim,
					  cellDim, cellDim, *this->moveCellImage);
	}

}

void UI::unitMenu(QPainter* p, Unit* u) {
	/*
	 * This menu get opened once the unit moved, it can now do several actions as attack, capture a city, nothing
	 */
	p->fillRect(this->selectedBox->getPosX()-10, this->selectedBox->getPosY()-10,
				this->selectedBox->getWidth()+10, this->selectedBox->getHeight()+10, Qt::red);
	for (MenuBox* box : *this->menuBoxes) {
		p->fillRect(box->getPosX(), box->getPosY(), box->getWidth(), box->getHeight(), Qt::white);
		p->drawRect(box->getPosX(), box->getPosY(), box->getWidth(), box->getHeight());
		p->drawText(box->getPosX(), box->getPosY(), QString::fromStdString(box->getTitle()));
	}
}

void UI::paint(QPainter *p, Unit *u)
{
	if (menuType == 0) {
		return; //nothing to paint here
	} else if (menuType == 1) { //move menu
		moveMenu(p,u);
	} else if (menuType == 2) { //unit menu
		unitMenu(p,u);
	}
}

void UI::setType(Unit* u, int t)
{
	clearMenuBoxes();
	menuType = t;
	if (menuType == 1) {
		this->moveCells = this->game->getMoveCells(u);
	}
	else if (menuType == 2) {//Unit menu
		std::cout << "Menu type 2" << std::endl;
		int swidth = cellDim*3;
		int sheight = cellDim;
		if (u->getCanAttack()) {
			this->menuBoxes->push_back(new AttackBox((width/2)-(swidth/2),(height/2)-(sheight*1.5),swidth,sheight));
		}
		Buildings* build = this->game->getBuildingOnPos(u->getPosX(), u->getPosY()); // !! MIGHT BE NULLPTR
		if (build != nullptr) {
			std::cout << "building not null" << std::endl;
		}
		if (build != nullptr) {
			if (build->getOwner()!=nullptr) {
			}
			if (build->getOwner()!=nullptr) {
				if (build->getOwner()->getTeamColor()!=u->getOwner()->getTeamColor()) {
					/* ennemy building */
					this->menuBoxes->push_back(new CaptureBox((width/2)-(swidth/2),
															  (height/2),
															  swidth, sheight));
				}
			} else {
				/* neutral building*/
				this->menuBoxes->push_back(new CaptureBox((width/2)-(swidth/2),
														  (height/2),
														  swidth, sheight));
			}
		}
		this->menuBoxes->push_back(new WaitBox((width/2)-(swidth/2), (height/2)+(sheight*1.5), swidth, sheight));
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

void UI::cursorDown() {
	int newPos = cursorPos;
	if (++newPos < this->menuBoxes->size()) { // Unit menu has only two options (for the moment): attack and wait
		cursorPos++;
		this->selectedBox = this->menuBoxes->at(cursorPos);
	}
}

void UI::cursorUp() {
	int newPos = cursorPos;
	if (--newPos >= 0) {
		cursorPos--;
		this->selectedBox = this->menuBoxes->at(cursorPos);
	}
}
