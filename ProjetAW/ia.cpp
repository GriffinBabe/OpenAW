#include "ia.h"
#include <cstdlib>
#include <tgmath.h>

IA::IA(int l, Player* p)
{
 level = l;            //c'est l'ia de NIVEAU BASIQUE
 player = p;
}

void IA::action(){
    std::vector<Buildings*>* buildings = getBuildings();
    for(Buildings* b : *buildings){
        if(b->getOwner() == player){
            createUnit(b,player,1); // si possible crée (une infanterie pour l'instant)
        }
    }

    std::vector<Unit*>* units= getUnits();
    for(Unit* u : *units){            //check les unités que l'ia possède
        if(u->getOwner() == player){
            movement(u);  //appelle la fonction qui va calculer et effectuer le mouvement pour cette unité
        }
    }
}

void IA::movement(Unit* u){
    std::vector<std::pair<int,int>> move = getMoveCells(u); //obtiens la liste des positions possible
    for(std::pair<int,int> p : move ){
        if (checkUnitOnPos(p.first,p.second)){   //regarde si il y a une unité sur cette position
            std::pair<int,int>pos = nextToTarget(move,p);
            moveUnit(u,pos);
            attack(u,getUnitOnPos(p.first,p.second),false); //attaque si possible
            break;
        }
        if (checkBuildingOnPos(p.first,p.second) && (u->getID()==1)||(u->getID()==2)){ //si n'a pas attaqué ce tour check si batiment accessible
                moveUnit(u,p);                         // s'y déplace
                capture(getBuildingOnPos(p.first,p.second)); //le capture si possible

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
