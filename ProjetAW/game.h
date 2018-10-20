#ifndef GAME_H
#define GAME_H

#include <vector>
#include "player.h"

class Game
{
public:
	Game();

	void setLocalPlayer(Player p);
	void newPlayer(Player p);
	Player& getLocalPlayer();

private:
	std::vector<Player> players; // List containing all the player
	Player localPlayer; // this is the player that is playing on this execution of the program
};

#endif // GAME_H
