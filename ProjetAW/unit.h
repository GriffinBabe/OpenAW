#ifndef UNIT_H
#define UNIT_H

#include "player.h"
#include <QDebug>

class Unit
{
public:
	Unit(Player& player);
	Player* owner;
};

#endif // UNIT_H
