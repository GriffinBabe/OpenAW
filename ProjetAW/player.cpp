#include "player.h"

Player::Player(std::string name, char tc)
{
	money = 1500;
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

int Player::getMoney(){return this->money;}

void Player::setMoney(int m){money = m;}
