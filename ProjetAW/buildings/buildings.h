#ifndef BUILDINGS_H
#define BUILDINGS_H

#include <vector>
#include <string>
#include "player.h"

class Buildings
{
public:
    Buildings();
	virtual ~Buildings();
    void setCpoint(int a);
    void setPosX(int x);
    void setPosY(int y);
    int getPosX();
    int getPosY();
    int getCpoint();
    int getCash();
    void setOwner(Player* owner);
    Player* getOwner();
	int getID();
	int getCellID();
protected:
    int posX;
    int posY;
    Player* owner;
    int capturepoint;
    int cash;
	int id; // 1 = factory, 2 = city NOTE that those are different IDs than cells id/data
	int cellId;
};

#endif // BUILDINGS_H
