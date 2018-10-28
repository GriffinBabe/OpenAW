#include "game.h"
#include <iostream>
#include <math.h>

Game::Game()
{
	this->map = new Map(":/Maps/map1.txt");
	std::vector<Player> players; // Initialises new player vector
	std::vector<Unit*> units;
	std::cout << "[Game Model] Game Initialised" << std::endl;
}

void Game::addPlayer(Player* p)
{
	players.push_back(p);
	std::cout << "[Game Model] Player with username " << p->getUsername() << " added to game." << std::endl;
}

void Game::addUnit(Unit* u)
{
	units.push_back(u);
}

Player* Game::getPlayerByUsername(std::string username) {
	std::vector<Player*>::iterator it;
	for (it = players.begin(); it != players.end(); ++it) {
		if ((*it)->getUsername().compare(username)==0) {return *it;}
	}
	return NULL;
}

std::vector<Unit *> *Game::getUnits()
{
	return &units;
}

std::vector<std::pair<int, int> > Game::getMoveCells(Unit* u)
{
	/*
	 * returns the a vector of pairs containing the position where the unit can move
	 */

	std::vector<std::pair<int,int>> moveCells;
	std::vector<std::vector<Cell>> cells = *this->map->getCells();
	std::vector<std::vector<Cell>>::iterator it;
	std::vector<Cell>::iterator it2;
	for (it=cells.begin(); it != cells.end(); ++it) {
		for (it2 = it->begin(); it2 != it->end(); ++it2) { //it2 is technically a cell
			if (unitCanMoveOnCell(u,(*it2))) {
				moveCells.push_back(std::pair<int,int>((*it2).getPosX(),(*it2).getPosY()));
			}
		}
	}
	return moveCells;
}

bool Game::unitCanMoveOnCell(Unit *u, Cell c)
{
	if (sqrt( pow(c.getPosX() - u->getPosX(), 2) + pow(c.getPosY() - u->getPosY(), 2)) > u->getMovementPoints()) {
		// If there is enough range, this is a simplified version and is going to be changed after
		return false;
	} else if ( (checkUnitOnPos(c.getPosX(), c.getPosY())) && (c.getPosX()!=u->getPosX() || c.getPosY()!= u->getPosY())) {
		// If there is a unit on this cell and this unit isn't the unit that we want to move
		return false;
	} else {
		// All is good, the unit can moove here
		return true;
	}
}

Player *Game::getLocalPlayer()
{
	return this->localPlayer;
}

Map* Game::getMap() {
	return this->map;
}

void Game::setLocalPlayer(Player *lp)
{
	this->localPlayer = lp;
}

void Game::moveUnit(Unit *u, std::pair<int, int> pos)
{
	if (unitCanMoveOnCell(u,this->map->getCellAt(pos.first,pos.second))) {
		u->setPos(pos.first,pos.second);
		u->setCanMove(false); // The unit moved and can't move anymore.
	} else {
		std::cout << "unit can't move on this position: " << pos.first << "; " << pos.second << std::endl;
	}
}

bool Game::checkUnitOnPos(int x,int y){ //check si il ya une unité à la position et renvoie cette unité
    std::vector<Unit*>::iterator it;
    for (it = units.begin(); it!=units.end(); ++it ){
        if ( ((*it)->getPosX() == x) && ((*it)->getPosY() == y) ){
            return true;
        }
    }
    return false;
}

Unit* Game::getUnitOnPos(int x, int y) {
    std::vector<Unit*>::iterator it;
    for (it = units.begin(); it!=units.end(); ++it ){
        if ( ((*it)->getPosX() == x) && ((*it)->getPosY() == y) ){
            return *it;
        }
    }
}

void Game::createUnit(Player* owner, std::pair<int,int> spawn){
	this->units.push_back(new Infantery(3,3,owner)); //infantery pour le test, UNIT_TYPE dans le futur
}

void Game::Capture(Buildings* b){
    if (checkUnitOnPos(b->getPosX(),b->getPosY()) == true){
        Unit* u = getUnitOnPos(b->getPosX(),b->getPosY());
        if(u->getOwner()!=b->getOwner()){
            if((u->getID() == 1)||(u->getID() == 2)){b->setCpoint(b->getCpoint() - u->getHealth());}
            if(b->getCpoint() >= 0){b->setOwner(u->getOwner()); b->setCpoint(20);}
        }
    }
//check si y a une unité ennemi sur le batiment, si c'est une infanterie ou bazooka, retire des points de capture
//au batiment, si les points de capture passe à 0 ou moins, change l'owner du batiment et reset les capture points

}
