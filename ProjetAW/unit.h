#ifndef UNIT_H
#define UNIT_H

#include <vector>
#include <string>
#include "player.h"


class Unit
{
public:
    Unit(Player player);
    Player* getOwner()const;
    int getHealth();
    void setHealth(int a);
    std::pair<int,int> getPos();
    std::pair<int,int> getDir();
    void setPos(std::pair<int,int> pos);
    void setDir(std::pair<int,int> dir);
    void setDamage(int d);
    int getDamage();
private:
    Player* owner;
    int health;
    int damage;
    std::pair<int,int> pos;
    std::pair<int,int> dir;
};
#endif // UNIT_H
