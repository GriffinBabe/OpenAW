#ifndef IA_H
#define IA_H
#include "game.h"

class IA : public Game
{
public:
    IA(int level, Player* p);
    void movement(Unit* u);
    void action();


private:
    int level; //niveau de difficulté
    Player* player; //joueur contrôlé par l'ia


};

#endif // IA_H
