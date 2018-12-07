#include "units/unit.h"

Unit::Unit(){}

Unit::Unit(Player player)
{
    *owner = player;
}

Player* Unit::getOwner()const{return this->owner;}

void Unit::setOwner(Player *ow)
{
	this->owner = ow;
}

void Unit::setHealth(int a){health = a;}

int Unit::getPosX() { return x;}

int Unit::getPosY() { return y;}

int Unit::getHealth(){return this->health;}

void Unit::setDamage(int d){damage = d;}

int Unit::getDamage(){return this->damage;}

int Unit::getDisp(){return this->disp;}

int Unit::getID(){return this->id;}

std::pair<int,int> Unit::getDir(){return dir;}

void Unit::setPos(int xi, int yi){x = xi; y = yi;}

void Unit::setDir(std::pair<int,int> d){dir = d;}

bool Unit::getCanAttack() { return canAttack; }

void Unit::setCanMove(bool c) {canMove = c;}

void Unit::setCanAttack(bool c) { canAttack = c;}

bool Unit::getCanMove() { return canMove; }

int Unit::getMovementPoints() { return movementPoints; }

int Unit::getMovementType() { return movementType;}

int Unit::getCost(){return cost;}

int Unit::getChartDamage(int u1, int u2)
{
	return damageChart[u1-1][u2-1];
}

std::string Unit::getName()
{
	return this->name;
}

