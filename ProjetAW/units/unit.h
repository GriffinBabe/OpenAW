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
	void setOwner(Player* ow);
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
    int getMovementType();
	bool getCanMove();
	bool getCanAttack();
	void setCanMove(bool c);
	void setCanAttack(bool c);
    int getCost();

	int getChartDamage(int u1, int u2); // Where u1 is attacker id and u2 is attacker id;


protected:
    Player* owner;
    int id, health, damage, disp, x, y, movementPoints,movementType,cost;
	bool canAttack;
	bool canMove;
    std::pair<int,int> dir;
    int damageChart[11][11] =	{{55,45,12,5,5,1,1,1,7,0,0},
                                 {65,55,85,65,55,15,5,15,9,0,0},
                                 {70,65,35,4,6,1,1,1,12,0,0},
                                 {105,105,60,45,25,10,1,5,120,65,75},
                                 {75,70,85,65,55,15,10,15,10,0,0},
                                 {105,95,105,105,85,55,25,45,12,0,0},
                                 {135,125,195,195,180,125,65,115,22,0,0},
                                 {125,115,125,115,105,75,35,55,22,0,0},
                                 {75,75,55,25,55,25,10,20,65,0,0},
                                 {0,0,0,0,0,0,0,0,100,55,100},
                                 {110,110,105,95,105,95,35,90,0,0,0}};
};


#endif // UNIT_H
