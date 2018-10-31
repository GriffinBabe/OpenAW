#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "player.h"
#include "units/unit.h"
#include "units/LandUnits/infantery.h"
#include "units/LandUnits/bazooka.h"
#include "units/LandVehicles/antiair.h"
#include "units/LandVehicles/recon.h"
#include "units/LandVehicles/tank.h"
#include "units/LandVehicles/mdtank.h"
#include "units/LandVehicles/megatank.h"
#include "units/LandVehicles/neotank.h"
#include "units/AirUnits/bcopter.h"
#include "units/AirUnits/bomber.h"
#include "units/AirUnits/fighter.h"
#include "buildings/buildings.h"
#include <vector>
#include <string>

class Game
{
public:
	//Model
	Game();
	void addPlayer(Player* p);
    void addUnit(Unit* u);
    void addBuilding(Buildings* b);
	Player* getPlayerByUsername(std::string username);

	//Controller & View

	std::vector<Unit*>* getUnits();
    std::vector<Buildings*>* getBuildings();
	std::vector<std::pair<int,int>> getMoveCells(Unit* u);
	std::vector<Unit*>* getAttackableUnits(Unit* u);
	Player* getLocalPlayer();

    //Model
	void createUnit(Unit* u);
    bool checkUnitOnPos(int x , int y);
	bool checkBuildingOnPos(int x, int y);
	Buildings* getBuildingOnPos(int x, int y);
    Unit* getUnitOnPos(int x, int y);
	Map* getMap();
	void setLocalPlayer(Player* lp);
	bool unitCanMoveOnCell(Unit* u, Cell c);
	void moveUnit(Unit* u, std::pair<int,int> pos);
	bool canCapture(Buildings* b);
	void capture(Buildings* b);
	bool canBuildFactory(Buildings* f, int unitID);
	bool canBuildAirport(Buildings* b, int unitID);
	void cashIncome(Player* p);
	bool attackable(Unit* u, Unit* unit, bool defensemode); // can u attack unit ?
	void setPlayerwhoplays(Player* p);
    Player* getPlayerwhoplays();
	void nextTurn();

	void attack(Unit* u1, Unit* u2, bool backfire);
	int getDamage(Unit* u1, Unit* u2);

private:
	Player* localPlayer;
    Player* playerwhoplays;
	std::vector<Unit*> units;
	std::vector<Player*> players;
    std::vector<Buildings*> buildings;
	Map* map;
    int tour;
};

#endif // GAME_H
