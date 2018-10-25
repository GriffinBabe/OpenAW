#include "game.h"
#include <iostream>

Game::Game()
{
	this->map = new Map(":/Maps/map1.txt");
	std::vector<Player> players; // Initialises new player vector
	std::vector<Unit*> units;
	std::cout << "[Game Model] Game Initialised" << std::endl;
	cursorX = 0;
	cursorY = 0;
	cellDim = 32; // Default cell dimension but will be overrided when MainWindow::setGame() called
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

void Game::setCursor(int x, int y)
/*
 * set cursor to target cell the parameters are mouse
 */
{
	cursorX = x/cellDim;
	cursorY = y/cellDim;
}

int Game::getCursorX()
{
	return cursorX;
}

int Game::getCursorY()
{
	return cursorY;
}

void Game::setCellDim(int dim)
{
	cellDim = dim;
}

void Game::selectElement()
/*
 *  This method selects the unit, building and cell where the cursor is.
 *  There is a priority to be respect and it's ruled by the return statement.
 */
{
	//Checks if there is any unit on it and selects it
	if (checkUnitOnPos(cursorX,cursorY)) { //We know that there is a unit
		this->selectedUnit = getUnitOnPos(cursorX, cursorY); //The selectedPointer unit is now set
		std::cout << "Unit selected with position: " << this->selectedUnit->getPosX()<< "; "
				  << this->selectedUnit->getPosY()<< std::endl;
		return;
	}
	std::cout << "No unit selected" << std::endl;
}

std::vector<Unit *> *Game::getUnits()
{
	return &units;
}

void Game::cursorDown() {
	int temp = cursorY + 1;
	if (temp <= this->map->getSizeY()) { // First put ++ before variable else the condition check will be false
		cursorY++;
	}
}

void Game::cursorLeft() {
	int temp = cursorX - 1;
	if (temp >= 0) {
		cursorX--;
	}
}

void Game::cursorRight() {
	int temp = cursorX + 1;
	if (temp <= this->map->getSizeX()) {
		cursorX++;
	}
}

void Game::cursorUp() {
	int temp = cursorY - 1;
	if (temp >= 0) {
		cursorY--;
	}
}

Map* Game::getMap() {
	return this->map;
}

Unit *Game::safeSelectedUnit()
{
    if (this->selectedUnit != NULL) {
        return this->selectedUnit;
    } else {
        throw "Selected Unit is a null pointer";
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
    this->units.push_back(new Infantery(3,3,owner));
}
