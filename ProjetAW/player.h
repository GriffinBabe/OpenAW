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
	Player(std::string name, char teamColor);
	Player(std::string name, char teamColor, int IALvl);
	std::string getUsername();
	char getTeamColor();

private:
	std::string username;
	int money;
	char teamColor;

};

#endif // PLAYER_H
