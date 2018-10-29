#ifndef FIGHTER_H
#define FIGHTER_H


#include "../unit.h"
class Fighter : public Unit

{
public:
    Fighter(int xi, int yi, Player* owner);
};

#endif // FIGHTER_H
