#ifndef BOMBER_H
#define BOMBER_H


#include "../unit.h"
class Bomber : public Unit

{
public:
    Bomber(int xi, int yi, Player* owner);
};

#endif // BOMBER_H
