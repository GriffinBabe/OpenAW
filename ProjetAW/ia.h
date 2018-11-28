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

    void adobjunit(Unit* objunit);   //rajoute un objectif à la liste
    void adobjbuild(Buildings* objbuild);
    std::vector<Unit*> getObjunit();  //retourne la liste des objectifs
    std::vector<Buildings*> getObjbuild();
    void resetObj(); //réinialise les listes d'objectifs
    bool checkifobj(Buildings* b);
    std::pair<int,int> getClosestAccessible(Unit* u,int x, int y); //position la plus proche de la cible

private:
    int level; //niveau de difficulté
    Player* player; //joueur contrôlé par l'ia
    Game* game;
    int maxUnitForMoney(bool AirType);
    int nextToAnEnnemy(std::pair<int,int> p);
    Buildings* closestBuilding(Unit* u);
    Unit* closestEnnemyUnit(Unit* u);
    std::vector<Unit*> objunit; //Liste des objectifs unités ennemis
    std::vector<Buildings*> objbuild; //liste des objectifs batiments ennemis
};

#endif // IA_H
