#ifndef TANK_H
#define TANK_H


#include "../unit.h"
class Tank : public Unit

{
public:
    Tank(int xi, int yi, Player* owner);
};
#endif // TANK_H
