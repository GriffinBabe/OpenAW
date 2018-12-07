#include "player.h"

Player::Player(std::string name, char tc)
{
	money = 1500;
	this->username = name;
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

int Player::getCountry()
{
	return country;
}

void Player::setCountry(int c)
{
	country = c;
}

int Player::getMoney(){return this->money;}

void Player::setMoney(int m){money = m;}
