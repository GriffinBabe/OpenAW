#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>

class Player
{
public:
	Player();
	Player(std::string usr);
	std::string getUsername();

private:
	char teamColor; // Blue Moon and Orang Star 'B' and 'O'
	//std::vector<Unit> units; //Player units
	std::string username; // units of the player
};

#endif // PLAYER_H
