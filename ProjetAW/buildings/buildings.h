#ifndef BUILDINGS_H
#define BUILDINGS_H

#include <vector>
#include <string>
#include "player.h"

class Buildings
{
public:
    Buildings();
    void setCpoint(int a);
    void setPosX(int x);
    void setPosY(int y);
    int getPosX();
    int getPosY();
    int getCpoint();
    int getCash();
    void setOwner(Player* owner);
    Player* getOwner();
protected:
    int posX;
    int posY;
    Player* owner;
    int capturepoint;
    int cash;
};

#endif // BUILDINGS_H
