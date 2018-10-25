#include "ui.h"
#include <iostream>
#include <vector>

UI::UI()
{
	this->arrow = new QPixmap(":/Images/arrow.png");
	this->moveCellImage = new QPixmap(":/Images/Terrain/moveCell.png");
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
	if (u->getCanMove()) {
		// In this case unit can move AND attack
		int swidth = cellDim*4;
		int sheight = cellDim*4;
		std::cout << "swidth " << swidth << std::endl;
		std::cout << "sheight " << sheight << std::endl;
		std::cout << "width " << width << std::endl;
		std::cout << "height " << height << std::endl;
		p->fillRect((width/2)-(swidth/2),
					(height/2)-(sheight/2),
					swidth, sheight, Qt::white);
		p->drawRect((width/2)-(swidth/2),
					(height/2)-(sheight/2),
					swidth, sheight);
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
