#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include <string>
#include "unit.h"

class Player
{
public:
	Player(std::string name);

	std::string username;

private:
	std::vector<Unit*>* units;
};

#endif // PLAYER_H
