#include "game.h"
#include <iostream>
#include <math.h>
#include <algorithm>

Game::Game()
{
	std::cout << "[Game Model] Game Initialised without map or startMoney" << std::endl;
	std::vector<Player> players; // Initialises new player vector
	std::vector<Unit*> units;
}

Game::Game(int mapId, int startMoney, int inc) : mapId(mapId), startMoney(startMoney)
{
	std::cout << "[Game Model] Game Initialised with a map and startMoney" << std::endl;
	income = inc;
	this->map = new Map(mapId);
	std::vector<Player> players;
	std::vector<Unit*> units;
	this->buildings = *map->getBuildings();
}


void Game::setMap(int id)
{
	this->mapId = id;
	this->map = new Map(id);
	this->buildings = *map->getBuildings();
}

int Game::getMapId()
{
	return mapId;
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
    reachableSquares.clear();
    int moveCostOnCell=movementCostsPerTerrain[u->getMovementType()-1][map->getCellAt(u->getPosX(),u->getPosY()).getMoveType()-1];
    recursiveMoveLoop((u->getMovementPoints()+moveCostOnCell),u->getPosX(),u->getPosY(),u,"init");
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


    //On compare toutes les positions accessibles avec la position de la cellule ciblée

    bool isInTheList=false;
    for (int i=0;i<reachableSquares.size();i++){
        if(reachableSquares[i].first==c.getPosX() && reachableSquares[i].second==c.getPosY()){
            isInTheList=true;

        }
    }

    return isInTheList;
}

void Game::recursiveMoveLoop(int nbMoves, int nextX,int nextY, Unit *u,std::string dir){
    if ((nextX<map->getSizeX()) && (nextY<map->getSizeY()) && (nextX>=0) && (nextY>=0)){
        int cost=movementCostsPerTerrain[u->getMovementType()-1][map->getCellAt(nextX,nextY).getMoveType()-1];
        nbMoves-=cost;

        if (nbMoves>=0 && (checkUnitOnPos(nextX,nextY)==false || (nextX==u->getPosX() && nextY==u->getPosY()))){
            //up
            if (dir!="down"){
                recursiveMoveLoop(nbMoves,nextX,nextY-1,u,"up");
            }
            //down
            if (dir!="up"){
                recursiveMoveLoop(nbMoves,nextX,nextY+1,u,"down");
            }
            //left
            if (dir!="right"){
                recursiveMoveLoop(nbMoves,nextX-1,nextY,u,"left");
            }
            //right
            if (dir!="left"){
                recursiveMoveLoop(nbMoves,nextX+1,nextY,u,"right");
            }
            reachableSquares.push_back(std::pair<int,int>(nextX,nextY));
        }
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


void Game::cashIncome(Player* p,bool unitRepaired){
    std::vector<Buildings*>::iterator it;
    for (it = buildings.begin(); it != buildings.end(); ++it) {
        if(p == (*it)->getOwner() && (*it)->getID() == 2){ // If the building is a city it has id == 2
            if (unitRepaired==false){
				p->setMoney(p->getMoney() + income);
            }
            if (unitRepaired==true){
				p->setMoney(p->getMoney() + (0.9*income));
            }

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
    bool repairCost=repairUnit(playerwhoplays);
    cashIncome(playerwhoplays,repairCost); //génère le cash des batiments -à la fin du tour- <- changé au début du tour du joueur qui va commencer à jouer maintenant, comme dans advance wars
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

//Repair the allied units on allied cities at the end of the turn
bool Game::repairUnit(Player* p)
{
    bool unitRepaired=false;
    std::vector<Unit*>::iterator it;
    for (it = units.begin(); it != units.end(); ++it) {
        if(p == (*it)->getOwner()){
            for (Buildings* b : this->buildings) {
                if (b->getOwner()!=nullptr) {

                    // Is a city or factory and the owner is the given player and the unit is not a plane
                    if (b->getOwner()==p && (b->getID()==2 ||b->getID()==1)&&(*it)->getMovementType()!=5) {
                        //Is the player at the same position that the city and is he hurt
                        if ((*it)->getPosX()==b->getPosX()&& (*it)->getPosY()==b->getPosY() && (*it)->getHealth()<10){

                            (*it)->setHealth((*it)->getHealth()+2);

                            if((*it)->getHealth()>10){ //Max Life is 10
                                (*it)->setHealth(10);
                            }
                            unitRepaired=true;
                        }
                    }
                    // Is a airport and the owner is the given player and the unit is a plane

                    if (b->getOwner()==p && (b->getID()==3)&&(*it)->getMovementType()==5){
                        //Is the player at the same position that the city and is he hurt
                        if ((*it)->getPosX()==b->getPosX()&& (*it)->getPosY()==b->getPosY() && (*it)->getHealth()<10){

                            (*it)->setHealth((*it)->getHealth()+2);

                            if((*it)->getHealth()>10){ //Max Life is 10
                                (*it)->setHealth(10);
                            }
                            unitRepaired=true;
                        }

                    }
                }

            }

        }

    }
	return unitRepaired;
}

void Game::setIncome(int inc)
{
	income = inc;
}
