#include "player.h"

Player::Player(std::string usr)
{
	username = usr;
	std::cout << "User created with username: " << std::endl;
}

std::string Player::getUsername()
{
	return username;
}
