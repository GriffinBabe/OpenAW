#ifndef PLAYER_H
#define PLAYER_H
#include "ia.h"
#include <vector>
#include <string>
class Player
		/*
		 * Player doesn't include units, all player/units interaction are in the unit or game class
		 */
{
public:
	Player(std::string name, char tc);
    void setIA(IA* ia);
    IA* getIA();
	std::string getUsername();
	char getTeamColor();
	int getCountry();
	void setCountry(int c);
    int getMoney();
	int country;
    void setMoney(int m);
private:
    IA* ia;
	std::string username;
	int money;
	char teamColor;

};

#endif // PLAYER_H
