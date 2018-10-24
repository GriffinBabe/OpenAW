#ifndef UNIT_H
#define UNIT_H

#include <vector>
#include <string>
#include "player.h"

class Unit
{
public:
    Unit(Player player);
    Player* getOwner();
    int getHealth();
    void setHealth(int a);
    std::vector<int> getPos();
    std::vector<int> getDir();
private:
    Player* owner;
    int health;
    std::vector<int> pos (int x,int y);
    std::vector<int> dir (int x,int y);
};
#endif // UNIT_H
