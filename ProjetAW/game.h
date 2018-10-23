#ifndef GAME_H
#define GAME_H

#include "player.h"
#include <vector>
#include "map.h"

class Game
{
public:
	Game();
	void yell();
	void addPlayer(Player* p);

private:
	Player* localPlayer;

	std::vector<Player*>* players;
};

#endif // GAME_H
