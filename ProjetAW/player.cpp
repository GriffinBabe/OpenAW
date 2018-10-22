#include "player.h"

Player::Player(std::string name)
{
	username = name;
	this->units = new std::vector<Unit*>;
}
