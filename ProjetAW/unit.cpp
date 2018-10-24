#include "unit.h"

Unit::Unit(Player player)
{
    *owner = player;
}

Player* Unit::getOwner(){return this->owner;}

void Unit::setHealth(int a){health = a;}

int Unit::getHealth(){return this->health;}
