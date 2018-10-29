#ifndef NEOTANK_H
#define NEOTANK_H


#include "../unit.h"
class NeoTank : public Unit

{
public:
    NeoTank(int xi, int yi, Player* owner);
};
#endif // NEOTANK_H
