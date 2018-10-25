#ifndef UNIT_H
#define UNIT_H

#include <vector>
#include <string>
#include "player.h"


class Unit
{
public:
    Unit();
    Unit(Player player);
    Player* getOwner()const;
    int getHealth();
    int getDisp();
    void setHealth(int a);
    int getPosX();
    int getPosY();
    std::pair<int,int> getDir();
    void setPos(int xi, int yi);
    void setDir(std::pair<int,int> dir);
    int getID();
    void setDamage(int d);
    int getDamage();
	int getMovementPoints();
	bool getCanMove();
	bool getCanAttack();

protected:
    Player* owner;
	int id, health, damage, disp, x, y, movementPoints;
	bool canAttack;
	bool canMove;
    std::pair<int,int> dir;
};


#endif // UNIT_H
