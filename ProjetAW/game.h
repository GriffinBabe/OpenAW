#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "player.h"
#include "units/unit.h"
#include "units/infantery.h"
#include <vector>
#include <string>

class Game
{
public:
	//Model
	Game();
	void addPlayer(Player* p);
    void addUnit(Unit* u);

	Player* getPlayerByUsername(std::string username);

	//Controller & View
	void cursorUp();
	void cursorDown();
	void cursorLeft();
	void cursorRight();
	void setCursor(int x, int y);
	int getCursorX();
	int getCursorY();
	void setCellDim(int dim);
	void selectElement();

	std::vector<Unit*>* getUnits();

    //Model
    void createUnit(Player* owner, std::pair<int,int> spawn);
    bool checkUnitOnPos(int x , int y);
    Unit* getUnitOnPos(int x, int y);
	Map* getMap();

private:
	Unit* safeSelectedUnit();
	Player* localPlayer;
	std::vector<Unit*> units;
	std::vector<Player*> players;
	Map* map;

	Unit* selectedUnit;
	int cellDim;
	int cursorX, cursorY;
};

#endif // GAME_H
