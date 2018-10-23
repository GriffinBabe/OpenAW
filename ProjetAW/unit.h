#ifndef UNIT_H
#define UNIT_H

#include "player.h"

class Unit
{
public:
    Unit(Player* owner);

private:
	Player* owner;
};

#endif // UNIT_H
