#include "player.h"
#include <iostream>

Player::Player(std::string usr)
{
	std::cout << "User created with username: " << usr << std::endl;
	username = usr;
}

std::string Player::getUsername()
{
	return username;
}
