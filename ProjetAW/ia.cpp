#include "ia.h"
#include "game.h"
#include <cstdlib>
#include <tgmath.h>
#include <chrono>
#include <thread>

IA::IA(int l, Player* p, Game* g)
{
 level = l;            //c'est l'ia de NIVEAU BASIQUE
 player = p;
 game = g;
}

void IA::play(){ //temporaire
    if(game->getPlayerwhoplays()==player){action();}
    std::cout << "l'ia joue" << std::endl;
    //std::this_thread::sleep_for(std::chrono::milliseconds(2000));
    game->nextTurn();
}

void IA::action(){
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));//Ajout de temps entre chaque action

    std::vector<Unit*>* units= game->getUnits();
    for(Unit* u : *units){            //check les unités que l'ia possède
        if(u->getOwner() == player){
            movement(u);  //appelle la fonction qui va calculer et effectuer le mouvement pour cette unité

        }
    }

    std::vector<Buildings*>* buildings = game->getBuildings();
    for(Buildings* b : *buildings){
        if(b->getOwner() == player && game->checkUnitOnPos(b->getPosX(),b->getPosY())==false){
            if (game->getPlayerCityCount(player)<8){
                game->createUnit(b,player,1); // Tant que le joueur n'a pas 8 villes,crée une infanterie
            }
            else if(player->getMoney()>Infantery(1,1,player).getCost()){
                game->createUnit(b,player,maxUnitForMoney(b->getID()==3)); //Crée une unité correspondant au type du batiment(aéroport ou usine)
            }

        }
    }
}

void IA::movement(Unit* u){
    std::vector<std::pair<int,int>> move = game->getMoveCells(u); //obtiens la liste des positions possible
    //Cette liste ne contient plus les positions des unités ennemies et alliées
    for(std::pair<int,int> p : move ){
        if(u->getCanMove()){
            //up
            if (nextToAnEnnemy(p)==1){
                Unit* u2=game->getUnitOnPos(p.first,p.second-1);
                if (game->getDamage(u,u2)>u2->getHealth() || (game->getDamage(u,u2)>game->getDamage(u2,u))){
                    game->moveUnit(u,p);
                    game->attack(u,u2,true);
                    break;
                }
            }//down
            if (nextToAnEnnemy(p)==2){
                Unit* u2=game->getUnitOnPos(p.first,p.second+1);
                if (game->getDamage(u,u2)>u2->getHealth() || (game->getDamage(u,u2)>game->getDamage(u2,u))){
                    game->moveUnit(u,p);
                    game->attack(u,u2,true);
                    break;
                }
            }//left
            if (nextToAnEnnemy(p)==3){
                Unit* u2=game->getUnitOnPos(p.first-1,p.second);
                if (game->getDamage(u,u2)>u2->getHealth() || (game->getDamage(u,u2)>game->getDamage(u2,u))){
                    game->moveUnit(u,p);
                    game->attack(u,u2,true);
                    break;
                }
            }if (nextToAnEnnemy(p)==4){
                Unit* u2=game->getUnitOnPos(p.first+1,p.second);
                if (game->getDamage(u,u2)>u2->getHealth() || (game->getDamage(u,u2)>game->getDamage(u2,u))){
                    game->moveUnit(u,p);
                    game->attack(u,u2,true);
                break;
                }
            }


        }
        if(u->getCanMove()){
            if (game->checkBuildingOnPos(p.first,p.second) && ((u->getID()==1)||(u->getID()==2))){ //si n'a pas attaqué ce tour check si batiment accessible
                if(game->getBuildingOnPos(p.first,p.second)->getOwner()!=player){ //L'unité ne se déplace pas sur une ville qu'elle possède déjà
                    if (game->checkUnitOnPos(p.first,p.second)==false || (u->getPosX()==p.first && u->getPosY()==p.second)){ //Pas d'unités sur la case, à part elle-même
                        game->moveUnit(u,p); // s'y déplace
                        game->capture(game->getBuildingOnPos(p.first,p.second));//le capture si possible
                    break;
                    }
                }
            }
        }

     }

    //Si après toutes ces conditions, l'unité peut encore se déplacer, elle se déplace aléatoirement
    if (u->getCanMove()){
        int a1=rand()%(move.size());
        game->moveUnit(u,move[a1]);

    }
     //il faudrait rajouter par la suite CheckBuildingOnPos , CheckRoadOnPos, etc.. avec des priorités d'action
     //garder en tête que ça reste le level  1 de l'IA --> actions de base
     //on implémentera des fonctions plus poussées (liste d'action d'etc...) au niveau 2 et 3
}

//Renvoie l'id de la meilleure unité terrestre que l'on puisse produire en fonction de son argent restant
int IA::maxUnitForMoney(bool AirType){
    int money=player->getMoney();
    if (AirType==true){
        if (money>Bomber(1,1,player).getCost()){
            return 11;
        }if (money>Fighter(1,1,player).getCost()){
            return 10;
        }if (money>BCopter(1,1,player).getCost()){
            return 9;
        }
    }else if (AirType==false){
        if (money>NeoTank(1,1,player).getCost()){
            return 8;
        }if (money>MegaTank(1,1,player).getCost()){
            return 7;
        }if (money>MdTank(1,1,player).getCost()){
            return 6;
        }if (money>AntiAir(1,1,player).getCost()){
            return 4;
        }if (money>Tank(1,1,player).getCost()){
            return 5;
        }if (money>Recon(1,1,player).getCost()){
            return 3;
        }if (money>Bazooka(1,1,player).getCost()){
            return 2;
        }if (money>Infantery(1,1,player).getCost()){
            return 1;
        }
    }else{
        std::cout<<"Erreur, le montant devrait permettre de créer une unité ci-dessus"<<std::endl;
    }

}
//Vérie s'il y a un ennemi accessible après un déplacement et renvoie la position de celui-ci
int IA::nextToAnEnnemy(std::pair<int,int> p){

    //up
    if (game->getUnitOnPos(p.first,p.second-1)!=nullptr && game->getUnitOnPos(p.first,p.second-1)->getOwner()!=player){
        return 1;
    }
    //down
    if (game->getUnitOnPos(p.first,p.second+1)!=nullptr && game->getUnitOnPos(p.first,p.second+1)->getOwner()!=player){
        return 2;
    }
    //left
    if (game->getUnitOnPos(p.first-1,p.second)!=nullptr && game->getUnitOnPos(p.first-1,p.second)->getOwner()!=player){
        return 3;
    }
    //right
    if (game->getUnitOnPos(p.first+1,p.second)!=nullptr && game->getUnitOnPos(p.first+1,p.second)->getOwner()!=player){
        return 4;
    }
    else{
        return 0;
    }

}

