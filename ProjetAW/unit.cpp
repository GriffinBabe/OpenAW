#include "unit.h"

Unit::Unit(Player player)
{
    *owner = player;
    health = 10;
}

Player* Unit::getOwner()const{return this->owner;}

void Unit::setHealth(int a){health = a;}

int Unit::getHealth(){return this->health;}

void Unit::setDamage(int d){damage = d;}

int Unit::getDamage(){return this->damage;}

std::pair<int,int> Unit::getPos(){return pos;}

std::pair<int,int> Unit::getDir(){return dir;}

void Unit::setPos(std::pair<int,int> p){pos = p;}

void Unit::setDir(std::pair<int,int> d){dir = d;}


// ---------------------------------------------

Infantery::Infantery(Player player) : Unit(player) {
    this->owner = &player;
}

