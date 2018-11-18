#include "ia.h"
#include "game.h"
#include <cstdlib>
#include <tgmath.h>

IA::IA(int l, Player* p, Game* g)
{
 level = l;            //c'est l'ia de NIVEAU BASIQUE
 player = p;
 game = g;
}

void IA::play(){ //temporaire
    if(game->getPlayerwhoplays()==player){action();}
    std::cout << "l'ia joue" << std::endl;
    game->nextTurn();
}

void IA::action(){
    std::vector<Unit*>* units= game->getUnits();
    for(Unit* u : *units){            //check les unités que l'ia possède
        if(u->getOwner() == player){
            movement(u);  //appelle la fonction qui va calculer et effectuer le mouvement pour cette unité
        }
    }

    std::vector<Buildings*>* buildings = game->getBuildings();
    for(Buildings* b : *buildings){
        if(b->getOwner() == player){
            game->createUnit(b,player,1); // si possible crée (une infanterie pour l'instant)
        }
    }
}

void IA::movement(Unit* u){
    std::vector<std::pair<int,int>> move = game->getMoveCells(u); //obtiens la liste des positions possible
    for(std::pair<int,int> p : move ){
        if (game->checkUnitOnPos(p.first,p.second)){   //regarde si il y a une unité sur cette position
            std::pair<int,int>pos = nextToTarget(move,p);
            game->moveUnit(u,pos);
            game->attack(u,game->getUnitOnPos(p.first,p.second),false); //attaque si possible
            break;
        }
        if (game->checkBuildingOnPos(p.first,p.second) && (u->getID()==1)||(u->getID()==2)){ //si n'a pas attaqué ce tour check si batiment accessible
            if(u->getCanMove()){
                game->moveUnit(u,p);                         // s'y déplace
                game->capture(game->getBuildingOnPos(p.first,p.second));//le capture si possible
            }
            break;
        }
    }
     //il faudrait rajouter par la suite CheckBuildingOnPos , CheckRoadOnPos, etc.. avec des priorités d'action
     //garder en tête que ça reste le level  1 de l'IA --> actions de base
     //on implémentera des fonctions plus poussées (liste d'action d'etc...) au niveau 2 et 3
}

std::pair<int,int> IA::nextToTarget(std::vector<std::pair<int,int>> m, std::pair<int,int> t){
   int x = t.first;
   int y = t.second;
   for(std::pair<int,int> p : m){
       if(sqrt((p.first  - x)^2 + (p.second - y)^2) == sqrt(2)){
           return p; //renvoie la première position atteignable par l'unité qui se trouve à 1 case de la cible
       }
   }
}
