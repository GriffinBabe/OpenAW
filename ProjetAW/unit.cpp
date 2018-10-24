#include "unit.h"

Unit::Unit(Player player)
{
    *owner = player;
}

Player* Unit::getOwner()const{return this->owner;}

void Unit::setHealth(int a){health = a;}

int Unit::getHealth(){return this->health;}

void Unit::setDamage(int d){damage = d;}

int Unit::getDamage(){return this->damage;}

pair<int,int> Unit::getPos(){return pos;}

pair<int,int> Unit::getDir(){return dir;}

void Unit::setPos(pair<int,int> p){pos = p;}

void Unit::setDir(pair<int,int> d){dir = d;}
