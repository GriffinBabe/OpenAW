#ifndef IA_H
#define IA_H
#include <iostream>
#include <vector>
class Player;
class Unit;
class Buildings;
class Game;
class IA
{
public:
    IA(int level, Player* p, Game* g);
    void movement(Unit* u);
    void action();
    std::pair<int,int> nextToTarget(std::vector<std::pair<int,int>> m ,std::pair<int,int> t);
    void play();
private:
    int level; //niveau de difficulté
    Player* player; //joueur contrôlé par l'ia
    Game* game;
    int maxUnitForMoney(bool AirType);
    int nextToAnEnnemy(std::pair<int,int> p);
    Buildings* closestBuilding(Unit* u);
    Unit* closestEnnemyUnit(Unit* u);

};

#endif // IA_H
