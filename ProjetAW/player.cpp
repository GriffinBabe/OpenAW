#include "player.h"

Player::Player(std::string name)
{
	username = name;
}

std::string Player::getUsername()
{
	return this->username;
}