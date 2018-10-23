#ifndef GAME_H
#define GAME_H

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
	void setCursor(int x, int y);
	int getCursorX();
	int getCursorY();

private:
	Player* localPlayer;
	std::vector<Unit> units;
	std::vector<Player> players;

	int cursorX, cursorY;
};

#endif // GAME_H
>>>>>>> c69b5c60240bfe75cf618edf19805eda09fd8b76
