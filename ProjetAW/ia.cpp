#include "ia.h"
#include <cstdlib>

IA::IA(int l, Player* p)
{
 level = l;
 player = p;
}

void IA::action(){
     std::vector<Unit*>* units= getUnits();
     for(Unit* u : *units){
         if(u->getOwner() == player){
             movement(u);
         }
     }
}

void IA::movement(Unit* u){
    std::vector<std::pair<int,int>> move = getMoveCells(u);
    int lenghtM = move.size();



}
