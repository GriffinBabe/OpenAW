#include "unit.h"
#include <iostream>

Unit::Unit(Player& player)
{
	this->owner = &player;
	std::cout << "Unit initialised with owner: " << this->owner->getUsername();
}
