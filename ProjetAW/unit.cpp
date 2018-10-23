#include "unit.h"
#include "player.h"

Unit::Unit(Player* player)
{
	this->owner = player;
}