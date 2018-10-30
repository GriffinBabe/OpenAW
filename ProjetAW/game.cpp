#include "game.h"
#include <iostream>
#include <math.h>
#include <algorithm>

Game::Game()
{
	this->map = new Map(":/Maps/map1.txt");
	std::vector<Player> players; // Initialises new player vector
	std::vector<Unit*> units;
	this->buildings = *map->getBuildings(); // Buildings are loaded into the map and the gathered by the game
	std::cout << "[Game Model] Game Initialised" << std::endl;
}

void Game::addPlayer(Player* p)
{
	players.push_back(p);
	if (players.size()==1) { // In this case whe know this is the first player we add
		this->playerwhoplays = players.at(0); // Sets the first player we add to te player who plays
	}
	std::cout << "[Game Model] Player with username " << p->getUsername() << " added to game." << std::endl;
}

void Game::addUnit(Unit* u)
{
	units.push_back(u);
}

void Game::addBuilding(Buildings* b){buildings.push_back(b);}


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

std::vector<Buildings *> *Game::getBuildings()
{
    return &buildings;
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

std::vector<Unit *> *Game::getAttackableUnits(Unit *u)
{
	std::vector<Unit*>* uns = new std::vector<Unit*>();
	for (Unit* unit : this->units) {
		if (attackable(u,unit,false)){ // Can u attack unit ?
			uns->push_back(unit);
		}
	}
	return uns;
}

bool Game::unitCanMoveOnCell(Unit *u, Cell c)
{
	if (u->getOwner() != this->playerwhoplays) {
		return false;
	}
	if (sqrt( pow(c.getPosX() - u->getPosX(), 2) + pow(c.getPosY() - u->getPosY(), 2)) > u->getMovementPoints()) {
		// If there is enough range, this is a simplified version and is going to be changed after
		return false;
	}
	if ( (checkUnitOnPos(c.getPosX(), c.getPosY())) && (c.getPosX()!=u->getPosX() || c.getPosY()!= u->getPosY())) {
		// If there is a unit on this cell and this unit isn't the unit that we want to move
		return false;
	}
	return true;
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
		u->setCanAttack(true);
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

bool Game::checkBuildingOnPos(int x, int y)
{
	std::vector<Buildings*>::iterator it;
	for (it = buildings.begin(); it != buildings.end(); ++it) {
		if ( (*it)->getPosX() == x && (*it)->getPosY() == y) {
			return true;
		}
	}
	return  false;
}

Buildings* Game::getBuildingOnPos(int x, int y) {
	std::vector<Buildings*>::iterator it;
	for (it = buildings.begin(); it != buildings.end(); ++it) {
		if ( (*it)->getPosX() == x && (*it)->getPosY() == y) {
			return *it;
		}
	}
	return nullptr;
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

void Game::capture(Buildings* b){
	if (canCapture(b)) {
		Unit* u = getUnitOnPos(b->getPosX(),b->getPosY());
		b->setCpoint(b->getCpoint() - u->getHealth());
		if (b->getCpoint() <= 0) {
			b->setOwner(u->getOwner());
			b->setCpoint(20);
		}
		u->setCanAttack(false);
	}
//check si y a une unité ennemi sur le batiment, si c'est une infanterie ou bazooka, retire des points de capture
	//au batiment, si les points de capture passe à 0 ou moins, change l'owner du batiment et reset les capture points
}

bool Game::canBuildFactory(Buildings *b, int unitID)
{
	if (this->checkUnitOnPos(b->getPosX(),b->getPosY())) {
		/* If there is a unit on the factory */
		return false;
	}
	if (b->getOwner()==nullptr) {
		return  false;
	}
	if (unitID == 1) { // Infatery
		if (b->getOwner()->getMoney() < 1000)
			return false;
	} else if (unitID == 2) { // Bazooka
		if (b->getOwner()->getMoney() < 3000)
			return  false;
	} else if (unitID == 3) { // Recon
		if (b->getOwner()->getMoney() < 4000)
			return  false;
	} else if (unitID == 4) { // AntiAir
		if (b->getOwner()->getMoney() < 8000)
			return  false;
	} else if (unitID == 5) { // Tank
		if (b->getOwner()->getMoney() < 7000)
			return  false;
	} else if (unitID == 6) { // MdTank
		if (b->getOwner()->getMoney() < 16000)
			return  false;
	} else if (unitID == 7) { // MegaTank
		if (b->getOwner()->getMoney() < 28000)
			return  false;
	} else if (unitID == 8) { // NeoTank
		if (b->getOwner()->getMoney() < 22000)
			return  false;
	} else {
		return false; // Unknown ID -> can't build that
	}
	return true;
}

bool Game::canCapture(Buildings* b) {
	if (checkUnitOnPos(b->getPosX(),b->getPosY()) == false) {
		return false;
	}
	Unit* capturer = this->getUnitOnPos(b->getPosX(),b->getPosY());
	if (capturer->getID()!=1 && capturer->getID()!=2) {
		// Only infantery and bazooka can capture
		return  false;
	}
	if (!capturer->getCanAttack()) {
		return false;
	}
	if (b->getOwner() != nullptr) {
		if (capturer->getOwner()->getTeamColor() != b->getOwner()->getTeamColor()) {
			return false;
		}
	}
	if (getUnitOnPos(b->getPosX(),b->getPosY())->getOwner() != this->playerwhoplays) {
		// If the owner of the capture unit is not the current playing player, do nothing
		return false;
	}
	return true;
}


void Game::cashIncome(Player* p){
    std::vector<Buildings*>::iterator it;
    for (it = buildings.begin(); it != buildings.end(); ++it) {
        if(p == (*it)->getOwner()){p->setMoney(p->getMoney() + (*it)->getCash());}

    }
	// add to the owner of the building the amount of money allowed by the building
}

/*
 * Can U attack Unit?
 * DefenseMode let's you attack even when you already did, this is for backfires during fights.
 */
bool Game::attackable(Unit *u, Unit *unit, bool defensemode)
{
	if (!defensemode && !u->getCanAttack()) {
		return false;
	}
	if (!defensemode && this->playerwhoplays!=u->getOwner()) {
		// If u if the initial attacker and his owner is not the player that should play now
		return false;
	}
	// No friendly fire
	if (u->getOwner()->getTeamColor()==unit->getOwner()->getTeamColor()) {
		return false;
	}
	// We can only attack units that are one cell close
	if ( sqrt( pow(u->getPosX()-unit->getPosX(),2) + pow(u->getPosY()-unit->getPosY(),2) ) > 1 ) {
		return  false;
	}
	return true;
}

void Game::setPlayerwhoplays(Player* p){playerwhoplays=p;}

Player* Game::getPlayerwhoplays(){return this->playerwhoplays;}


void Game::nextTurn(){
    std::vector<Player*>::iterator it;
    for (it = players.begin(); it != players.end(); ++it){  //passe son tour au joueur suivant
		if (getPlayerwhoplays()==*(it) && it != players.end()-1){
			setPlayerwhoplays(*(it+1));
			this->localPlayer = this->playerwhoplays; // This is TEMPORARY and is here
			// only for testing purposes;
			break;
		}
		if(getPlayerwhoplays()==*(it) && it == players.end()-1){
			setPlayerwhoplays(*(players.begin()));
			this->localPlayer = this->playerwhoplays; // This is TEMPORARY and is here
			// only for testing purposes;
			break;
		}
	}
	cashIncome(playerwhoplays); //génère le cash des batiments -à la fin du tour- <- changé au début du tour du joueur qui va commencer à jouer maintenant, comme dans advance wars
	for (Unit* u : units) {
		if (u->getOwner() == this->playerwhoplays) {
			u->setCanMove(true);
			u->setCanAttack(false);
		}
	}
}

/*
 * Unit u1 is the attacker, unit u2 is the defender. After the attack,
 * if the backfire is set on true and the defender is still alive, the function
 * gets recalled but without backfire!
 */
void Game::attack(Unit *u1, Unit *u2, bool backfire)
{
	if (attackable(u1,u2,!backfire)) { // Checks if u1 can attack u2
									// Reverted Backfire is given as parameter because we want to let the defender backfire even if he didn't attacked yet.
		u2->setHealth(u2->getHealth() - getDamage(u1,u2)); // Reduces U2 health
		if (u2->getHealth() <= 0) { // If u2 dies
			units.erase(std::remove(units.begin(), units.end(), u2), units.end());
		}
		u1->setCanAttack(false);
		if (u2->getHealth() > 0 && backfire) { // if u2 is still alive and the backfire is on
			attack(u2, u1, false); // Note that the unit are reversed because u2 backfires and becomes the attacker
		}
	}
}


/*
 *  This is the damage formula given in the project instructions
 *  u1 is the attacker, u2 is the defender
 */
int Game::getDamage(Unit *u1, Unit *u2)
{
	int B = u1->getChartDamage(u1->getID(),u2->getID());
	int A_HP = u1->getHealth(); // TODO: change if aerial
	int D_HP = u2->getHealth(); // TODO: change if aerial
	int D_TR = this->map->getCellAt(u2->getPosX(),u2->getPosY()).getDefense();
	if (u2->getID() == 9 || u2->getID() == 10 || u2->getID() == 11) { // If the defender U2 is an aerial unit
		D_TR = 0;
	}
	int damage =  B * A_HP / 10 * (100 - D_TR * D_HP) / 100;
	return damage/10;
}
