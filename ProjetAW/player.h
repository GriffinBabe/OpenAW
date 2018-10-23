#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>

class Player
		/*
		 * Player doesn't include units, all player/units interaction are in the unit or game class
		 */
{
public:
	Player(std::string name);
	Player(std::string name, int IALvl);
	std::string getUsername();

private:
	std::string username;
	int money;

};

#endif // PLAYER_H