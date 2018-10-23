#ifndef UNIT_H
#define UNIT_H

#include "player.h"

class Unit
{
public:
	Unit(Player* p);

private:
	Player* owner;
};

#endif // UNIT_H