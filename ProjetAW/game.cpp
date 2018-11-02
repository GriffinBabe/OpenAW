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

    if ( (checkUnitOnPos(c.getPosX(), c.getPosY())) && (c.getPosX()!=u->getPosX() || c.getPosY()!= u->getPosY())) {
		// If there is a unit on this cell and this unit isn't the unit that we want to move
		Unit* u2 = getUnitOnPos(c.getPosX(), c.getPosY()); // this is the unit on that place, we check that so we can fuse units!
		if (u2->getOwner() == u->getOwner() && u2->getID() == u->getID() && u2->getHealth() + u->getHealth() <= 10 && u2->getHealth() < 10 ) {
			return  true;
		}
		return false;
	}

    //On récupère de la fonction unitRange une liste de toutes les cases accessibles
    //en fonction du terrain et de l'unité. On la compare avec la position de la cellule c
    std::vector<std::pair<int,int>> reachableSquares;

    reachableSquares=unitRange(u);

    bool isInTheList=false;
    for (int i=0;i<reachableSquares.size();i++){
        if(reachableSquares[i].first==c.getPosX() && reachableSquares[i].second==c.getPosY()){
            isInTheList=true;

        }

    }
    return isInTheList;
}

std::vector<std::pair<int,int>> Game::unitRange(Unit *u){
    int Xcenter=u->getPosX();
    int Ycenter=u->getPosY();
    int nbMoves=u->getMovementPoints();
    int unitType=u->getMovementType();


    std::vector<std::pair<int,int>> reachableSquares;
    nbMoves+=1;

    //right
    for (int i=0;i<=u->getMovementPoints();i++){
        if (Xcenter+i<map->getSizeX()&& Xcenter-i>=0){
            int cost=movementCostsPerTerrain[unitType-1][map->getCellAt(Xcenter+i,Ycenter).getMoveType()-1];

            if(cost==100 || (nbMoves-cost)<0){
                break;
            }
            nbMoves-=cost;
            reachableSquares.push_back(std::pair<int,int>(Xcenter+i,Ycenter));
        }


    }
    //down
    nbMoves=u->getMovementPoints();
    nbMoves+=1;
    for (int i=0;i<=u->getMovementPoints();i++){
        if (Ycenter+i<map->getSizeY()&& Ycenter-i>=0){
            int cost=movementCostsPerTerrain[unitType-1][map->getCellAt(Xcenter,Ycenter+i).getMoveType()-1];

            if(cost==100 || (nbMoves-cost)<0){
                break;
            }
            nbMoves-=cost;
            reachableSquares.push_back(std::pair<int,int>(Xcenter,Ycenter+i));
        }


    }

    //up
    nbMoves=u->getMovementPoints();
    nbMoves+=1;
    for (int i=0;i<=u->getMovementPoints();i++){
        if (Ycenter+i<map->getSizeY()&& Ycenter-i>=0){
            int cost=movementCostsPerTerrain[unitType-1][map->getCellAt(Xcenter,Ycenter-i).getMoveType()-1];
            std::cout<<cost<<std::endl;
            if(cost==100 || (nbMoves-cost)<0){
                break;
            }
            nbMoves-=cost;
            reachableSquares.push_back(std::pair<int,int>(Xcenter,Ycenter-i));
        }


    }
    //left
    nbMoves=u->getMovementPoints();
    nbMoves+=1;
    for (int i=0;i<=u->getMovementPoints();i++){
        if (Xcenter+i<map->getSizeX()&& Xcenter-i>=0){
            int cost=movementCostsPerTerrain[unitType-1][map->getCellAt(Xcenter-i,Ycenter).getMoveType()-1];

            if(cost==100 || (nbMoves-cost)<0){
                break;
            }
            nbMoves-=cost;
            reachableSquares.push_back(std::pair<int,int>(Xcenter-i,Ycenter));
        }


    }

    return reachableSquares;
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
		/*
		 *  There is a unit on that cell AND from unitCanMoveOnCell()
		 *	we know we can move there => we are 100% sure this is a fusing action
		 */
		if (checkUnitOnPos(pos.first,pos.second) && (pos.first != u->getPosX() && pos.second != u->getPosY())) {
			Unit* u2 = getUnitOnPos(pos.first,pos.second);
			u2->setHealth(u2->getHealth() + u->getHealth());
			units.erase(std::remove(units.begin(), units.end(), u), units.end());
		} else { //Simple movement
			u->setPos(pos.first,pos.second);
			u->setCanMove(false); // The unit moved and can't move anymore.
			u->setCanAttack(true);
		}
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


void Game::createUnit(Buildings* b, Player* p, int unitID) {
	Unit* u = nullptr;
	switch(unitID) {
		case 1:
			u = new Infantery(b->getPosX(),b->getPosY(),p); break;
		case 2:
			u = new Bazooka(b->getPosX(),b->getPosY(),p); break;
		case 3:
			u = new Recon(b->getPosX(),b->getPosY(),p); break;
		case 4:
			u = new AntiAir(b->getPosX(),b->getPosY(),p); break;
		case 5:
			u = new Tank(b->getPosX(),b->getPosY(),p); break;
		case 6:
			u = new MdTank(b->getPosX(),b->getPosY(),p); break;
		case 7:
			u = new MegaTank(b->getPosX(),b->getPosY(),p); break;
		case 8:
			u = new NeoTank(b->getPosX(),b->getPosY(),p); break;
		case 9:
			u = new BCopter(b->getPosX(),b->getPosY(),p); break;
		case 10:
			u = new Bomber(b->getPosX(),b->getPosY(),p); break;
		case 11:
			u = new Fighter(b->getPosX(),b->getPosY(),p); break;
	}
	if (u==nullptr) { // No ID Match
		throw "No ID Match in Unit creation";
	}
	if (canBuild(b, u->getID())) {
		p->setMoney(p->getMoney() - u->getCost());
		u->setOwner(p);
		units.push_back(u);
	}
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

bool Game::canBuild(Buildings *b, int unitID)
{
	if (this->checkUnitOnPos(b->getPosX(),b->getPosY())) {
		/* If there is a unit on the factory */
		return false;
	}
	if (b->getOwner()==nullptr) {
		return  false;
	}
	if (unitID >= 1 && unitID <= 8) {
		if (b->getID()!=1) { // If we want to create a land unit and the building isn't a factory !
			return false;
		}
	}
	else if (unitID >= 9 && unitID <= 11) {
		if (b->getID()!=3) { // If we want to create an air unit and the building isn't an airport !
			return false;
		}
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
	} else if (unitID == 9) { // Bcopter
		if (b->getOwner()->getMoney() < 9000) {
			return false;
		}
	} else if (unitID == 10) { // bomber
		if (b->getOwner()->getMoney() < 22000) {
			return false;
		}
	} else if (unitID == 11) { // fighter
		if (b->getOwner()->getMoney() < 20000) {
			return false;
		}
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
		if (capturer->getOwner()->getTeamColor() == b->getOwner()->getTeamColor()) {
			return false;
		}
	}
	if (capturer->getOwner() == b->getOwner()) {
		return false;
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
		if(p == (*it)->getOwner() && (*it)->getID() == 2){ // If the building is a city it has id == 2
			p->setMoney(p->getMoney() + (*it)->getCash());
		}

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

int Game::getPlayerCityCount(Player *p)
{
	int count = 0;
	for (Buildings* b : this->buildings) {
		if (b->getOwner()!=nullptr) {
			if (b->getOwner()==p && b->getID()==2) { // Is a city and the owner is the given player
				count++;
			}
		}
	}
	return count;
}

int Game::getPlayerUnitCount(Player* p) {
	int count = 0;
	for (Unit* u : this->units) {
		if (u->getOwner() == p) {
			count++;
		}
	}
	return count;
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
	float damage =  B * A_HP / 10 * (100 - D_TR * D_HP) / 100;
	int totdmg = static_cast<int>(damage/10); // Everything after , is deleted
	float remaining = damage/10 - static_cast<int>(damage/10); // We get the remaining value after ,
	if (remaining >= .5f) {
		totdmg++; // We round up if the remaining value after , is 0,5 or bigger !
	}
	std::cout << "Damage fight from " << u1->getOwner()->getUsername() << " to " << u2->getOwner()->getUsername() << ": " << damage/10 << std::endl;
	std::cout << "int converted damage: " << totdmg << std::endl;
	return totdmg;
}
