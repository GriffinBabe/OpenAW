#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "player.h"
#include "units/unit.h"
#include <vector>
#include <string>

class Game
{
public:
	//Model
	Game();
	void addPlayer(Player p);
	void addUnit(Unit u);

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

    //Model
    Unit* checkpos(int x , int y);
    void createUnit(Player* owner, std::pair<int,int> spawn);
	Map* getMap();

private:
	Player* localPlayer;
    std::vector<Unit*> units;
    std::vector<Player> players;
	Map* map;

	int cellDim;
	int cursorX, cursorY;
};

#endif // GAME_H
