#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "player.h"
#include "units/unit.h"
#include "units/infantery.h"
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
	bool unitCanMoveOnCell(Unit* u, Cell c);
	Player* getLocalPlayer();

    //Model
    void createUnit(Player* owner, std::pair<int,int> spawn);
    bool checkUnitOnPos(int x , int y);
	bool checkBuildingOnPos(int x, int y);
	Buildings* getBuildingOnPos(int x, int y);
    Unit* getUnitOnPos(int x, int y);
	Map* getMap();
	void setLocalPlayer(Player* lp);
	void moveUnit(Unit* u, std::pair<int,int> pos);
	void capture(Buildings* b);
	void cashIncome(Player* p);

private:
	Player* localPlayer;
	std::vector<Unit*> units;
	std::vector<Player*> players;
    std::vector<Buildings*> buildings;
	Map* map;
    int tour;
};

#endif // GAME_H
