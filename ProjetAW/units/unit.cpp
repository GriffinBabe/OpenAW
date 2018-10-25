#include "units/unit.h"
Unit::Unit(){}
Unit::Unit(Player player)
{
    *owner = player;
}

Player* Unit::getOwner()const{return this->owner;}

void Unit::setHealth(int a){health = a;}

int Unit::getHealth(){return this->health;}

void Unit::setDamage(int d){damage = d;}

int Unit::getDamage(){return this->damage;}

int Unit::getDisp(){return this->disp;}

int Unit::getID(){return this->id;}

std::pair<int,int> Unit::getPos(){return pos;}

std::pair<int,int> Unit::getDir(){return dir;}

void Unit::setPos(std::pair<int,int> p){pos = p;}

void Unit::setDir(std::pair<int,int> d){dir = d;}

