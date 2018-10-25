#include "player.h"

Player::Player(std::string name, char tc)
{
	username = name;
	teamColor = tc;
}

std::string Player::getUsername()
{
	return this->username;
}

char Player::getTeamColor()
{
	return teamColor;
}
