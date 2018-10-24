#ifndef GAME_H
#define GAME_H

#include "map.h"
#include "player.h"
#include "unit.h"
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

	//Controller
	void cursorUp();
	void cursorDown();
	void cursorLeft();
	void cursorRight();
	void setCursor(int x, int y);
	int getCursorX();
	int getCursorY();

	Map* getMap();

private:
	Player* localPlayer;
	std::vector<Unit> units;
	std::vector<Player> players;
	Map* map;

	int cursorX, cursorY;
};

#endif // GAME_H
