#include "buildings.h"

Buildings::Buildings()
{

}

Buildings::~Buildings()
{
    //delete this;
}

void Buildings::setCpoint(int a){capturepoint = a;}

int Buildings::getCpoint(){return this->capturepoint;}

int Buildings::getPosX(){return this->posX;}

int Buildings::getPosY(){return this->posY;}

void Buildings::setPosX(int x){posX = x;}

void Buildings::setPosY(int y){posY = y;}

int Buildings::getCash(){return this->cash;}

void Buildings::setOwner(Player* newowner){owner = newowner;}

Player* Buildings::getOwner(){return this->owner;}

int Buildings::getID(){return this->id;}

int Buildings::getCellID()
{
	return cellId;
}
