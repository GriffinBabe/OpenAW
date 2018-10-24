#ifndef UNIT_H
#define UNIT_H

#include <vector>
#include <string>
#include "player.h"

using namespace std;

class Unit
{
public:
    Unit(Player player);
    Player* getOwner()const;
    int getHealth();
    void setHealth(int a);
    pair<int,int> getPos();
    pair<int,int> getDir();
    void setPos(pair<int,int> pos);
    void setDir(pair<int,int> dir);
    void setDamage(int d);
    int getDamage();
private:
    Player* owner;
    int health;
    int damage;
    pair<int,int> pos;
    pair<int,int> dir;
};
#endif // UNIT_H
