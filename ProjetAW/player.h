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
	Player(std::string name, char tc);
	Player(std::string name, char tc, int IALvl);
	std::string getUsername();
	char getTeamColor();
    int getMoney();
    void setMoney(int m);
private:
	std::string username;
	int money;
	char teamColor;

};

#endif // PLAYER_H
