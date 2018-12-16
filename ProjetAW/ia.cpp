#include "ia.h"
#include "game.h"
#include <cstdlib>
#include <tgmath.h>
#include <chrono>
#include <thread>
#include "networking/networkclient.h"


IA::IA(int l, Player* p, Game* g)
{
    level = l;            // level=0 : IA inactive
    player = p;           // level=1 :IA générique
    game = g;             // level=2 :IA greedy
                          // level=3 :IA Recon
                          // level=4 :IA Anti-Recon
    std::vector<Unit*>* objunit;        // Liste des objectifs unités ennemis
    std::vector<Buildings*>* objbuild;  // liste des objectifs batiments ennemis
}
void IA::play(){
    if(game->getPlayerwhoplays() == player){
        action();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        //MainWindow()->getNeworkClient()->endOfTurn();
        //client->endOfTurn();                        Ces 2 dernières lignes ne marchent pas. Quel est le problème?
        //game->nextTurn();
    }
    std::cout << "l'ia joue" << std::endl;

}
void IA::action(){
    //std::this_thread::sleep_for(std::chrono::milliseconds(1000));//Ajout de temps entre chaque action
    std::vector<Unit*>* units = game->getUnits();
    std::vector<Buildings*>* buildings = game->getBuildings();
    //IA inactive
    if  (level==0){
    }
    //IA générique
    if (level==1){
        for(Unit* u : *units){            //check les unités que l'ia possède
            if(u->getOwner() == player){
                movement(u,level);  //appelle la fonction qui va calculer et effectuer le mouvement pour cette unité
            }
        }
        for(Unit* u : *units){            //je le repète (c'est moche mais si tu veux romain fait un truc plus joli, j'ai plus le temps)
                                          //dans le cas où deux rangées d'unités sont collées et que celle derrière n'a pas pu bouger
            if(u->getOwner() == player && u->getCanMove()){
               movement(u,level);  //appelle la fonction qui va calculer et effectuer le mouvement pour cette unité
            }
        }
        for(Buildings* b : *buildings){
            if(b->getOwner() == player && game->checkUnitOnPos(b->getPosX(),b->getPosY())==false){
                if(b->getID()==3 && player->getMoney()>BCopter(1,1,player).getCost()){
                    int id = maxUnitForMoney(true);
                    if(id != 100){
                        game->createUnit(b,player,id);//Crée une unité dans un aéroport en premier lieu
                    }
                }
            }
        }
        for(Buildings* b : *buildings){
            if(b->getOwner() == player && game->checkUnitOnPos(b->getPosX(),b->getPosY())==false){
                if (game->getPlayerCityCount(player)<5){
                    game->createUnit(b,player,1); // Tant que le joueur n'a pas 8 villes,crée une infanterie
                }
                else if(player->getMoney()>1000 && game->getPlayerCityCount(player)<10 && game->getPlayerCityCount(player)>=5){
                    game->createUnit(b,player,maxUnitForMoney(false)); //Crée une unité dans une usine
                }
                else if(player->getMoney()>3000 && game->getPlayerCityCount(player)>= 10 && game->getPlayerCityCount(player) < 15 ){ //pour économiser de l'argent sinon dans le endgame ne fait pas de gros blindé
                    game->createUnit(b,player,maxUnitForMoney(false)); //Crée une unité dans une usine
                }
                else if(player->getMoney()>7000 && game->getPlayerCityCount(player)>=15){ //pour économiser de l'argent sinon dans le endgame ne fait pas de gros blindé
                    game->createUnit(b,player,maxUnitForMoney(false)); //Crée une unité dans une usine
                }
            }
        }
        resetObj();
    }
    //IA Greedy
    //Cette IA se joue contre l'ia inactive et va se déplacer pour capturer le plus rapidement possible toutes les villes
    if (level==2){
        for(Unit* u : *units){            //check les unités que l'ia possède
            if(u->getOwner() == player){
                movement(u,level);  //appelle la fonction qui va calculer et effectuer le mouvement pour cette unité
            }
        }
        for(Buildings* b : *buildings){
            if(b->getOwner() == player && game->checkUnitOnPos(b->getPosX(),b->getPosY())==false){
                if (game->getPlayerUnitCount(player)<1){
                game->createUnit(b,player,1); // Tant que le joueur n'a pas 1 infanterie, il en crée une
                }
            }
        }
        resetObj();
    }
    //IA Recon: elle cherche à battre l'IA greedy le plus vite possible en ne produisant que des unités infantery, bazooka ou Recon
    if (level==3){

        for(Unit* u : *units){            //check les unités que l'ia possède
            if(u->getOwner() == player){
                movement(u,level);  //appelle la fonction qui va calculer et effectuer le mouvement pour cette unité
            }
        }
        for(Buildings* b : *buildings){
            if(b->getOwner() == player && game->checkUnitOnPos(b->getPosX(),b->getPosY())==false){
                if (game->getPlayerCityCount(player)<5){
                    game->createUnit(b,player,1); // Tant que le joueur n'a pas 5 villes, il crée une infanterie
                }
                else if(player->getMoney()>1000){
                    game->createUnit(b,player,reconUnit()); //Sinon, s'il a l'argent, il crée une unité
                }
            }
        }
        resetObj();
    }
    //IA Anti-Recon : Elle bat l'IA Recon le plus rapidement possible en utilisant des chars et des avions notamment
    if (level==4){

        for(Unit* u : *units){            //check les unités que l'ia possède
            if(u->getOwner() == player){
                movement(u,level);  //appelle la fonction qui va calculer et effectuer le mouvement pour cette unité
            }
        }
        for(Buildings* b : *buildings){
            if(b->getOwner() == player && game->checkUnitOnPos(b->getPosX(),b->getPosY())==false){
                if(b->getID()==3 && player->getMoney()>BCopter(1,1,player).getCost()){
                    game->createUnit(b,player,antiReconMaxUnit(true));//Crée une unité dans un aéroport en premier lieu
                }
            }
        }
        for(Buildings* b : *buildings){
            if(b->getOwner() == player && game->checkUnitOnPos(b->getPosX(),b->getPosY())==false){
                if (game->getPlayerCityCount(player)<5){
                    game->createUnit(b,player,1); // Tant que le joueur n'a pas 5 villes, il crée une infanterie
                }
                else if(player->getMoney()>1000){
                    game->createUnit(b,player,antiReconMaxUnit(false));
                }
            }
        }
        resetObj();
    }

}

void IA::movement(Unit* u,int level){
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
        //Le joueur contine la capture s'il est déjà sur une ville neutre ou alliée
        if(u->getCanMove()){
            if (game->checkBuildingOnPos(u->getPosX(),u->getPosY()) && ((u->getID()==1)||(u->getID()==2))){
                if(game->getBuildingOnPos(u->getPosX(),u->getPosY())->getOwner()!=player){
                    p.first=u->getPosX();
                    p.second=u->getPosY();
                    game->moveUnit(u,p);
                    game->capture(game->getBuildingOnPos(p.first,p.second));
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

    //Si après toutes ces conditions, l'unité peut encore se déplacer, elle se déplace vers un objectif

    if (u->getCanMove()){
        Unit* e = closestEnnemyUnit(u);
        Buildings* b = closestBuilding(u);
        std::cout<<"closestbuildingOk"<< std::endl;
        double distB = sqrt (pow(u->getPosX() - b->getPosX(),2) + pow(u->getPosY() - b->getPosY(),2));
        double distU = 100;
        if(e!=NULL){
            distU = sqrt (pow(u->getPosX() - e->getPosX(),2) + pow(u->getPosY() - e->getPosY(),2));


            std::cout<<"distbu "<<distB<<" "<<distU<<std::endl;


            if(distU<=distB ||((u->getID()!=1)&&(u->getID()!=2))){
                //se déplace en direction de l'unité la plus proche
                std::cout<<"se déplace vers unité"<<std::endl;
                adobjunit(e);
                std::cout<<e->getPosX()<<e->getPosY()<<std::endl;
                game->moveUnit(u,getClosestAccessible(u,e->getPosX(),e->getPosY()));
            }
        }

        if(distB<distU && ((u->getID()==1)||(u->getID()==2))){
            adobjbuild(b);
            std::cout<<"addedobj"<<std::endl;
            //se déplace en direction du batiment objectif
            game->moveUnit(u,getClosestAccessible(u,b->getPosX(),b->getPosY()));
         }

    }

    //Si après toutes ces conditions, l'unité peut encore se déplacer, elle se déplace aléatoirement
    //gardé pour test, on peut delete

    if (u->getCanMove()){
        std::cout<<"randoooooom"<<std::endl;
        srand(time(NULL));
        int a1=rand()%(move.size());
        game->moveUnit(u,move[a1]);
    }


}
int IA::reconUnit(){
    int money=player->getMoney();
    srand(time(NULL));
    if (money>Recon(1,1,player).getCost()&& ((rand()%3==1))){
        return 3;
    }if (money>Bazooka(1,1,player).getCost() && rand()%3==0){
        return 2;
    }if (money>Infantery(1,1,player).getCost()){
    return 1;
    }
}
int IA::antiReconMaxUnit(bool AirType){
    int money=player->getMoney();
    if (AirType==true){
        if (money>Bomber(1,1,player).getCost() && ((rand()%3==1))){
            return 11;
        }if (money>Fighter(1,1,player).getCost()&& rand()%3==1){
            return 10;
        }if (money>BCopter(1,1,player).getCost()){
            return 9;
        }
    }else if (AirType==false){
        if (money>NeoTank(1,1,player).getCost()&& ((rand()%2==1))){
            return 8;
        }if (money>MegaTank(1,1,player).getCost() && rand()%2==1){
            return 7;
        }if (money>MdTank(1,1,player).getCost()&& rand()%2==1){
            return 6;
        }if (money>AntiAir(1,1,player).getCost()&& rand()%5==1){
            return 4;
        }if (money>Tank(1,1,player).getCost() && rand()%2==1 ){
            return 5;
        }if (money>Recon(1,1,player).getCost()&& ((rand()%2==1))){
            return 3;

        }if (money>Bazooka(1,1,player).getCost() && rand()%2==0){
            return 2;
        }if (money>Infantery(1,1,player).getCost()){
            return 1;
        }
    }

}
//IA Générique: Renvoie l'id de la meilleure unité terrestre que l'on puisse produire en fonction de son argent restant
int IA::maxUnitForMoney(bool AirType){
    int money=player->getMoney();
    srand(time(NULL));
    std::cout<<rand()%2<<std::endl;
    bool air = checkifair();
    bool blinde = checkifblinde();
    if (AirType==true){
        if (money>Bomber(1,1,player).getCost() && ((rand()%3==1 && blinde)||(rand()%5==1))){
            return 11;
        }if (money>Fighter(1,1,player).getCost()&& rand()%3==1 && air){
            return 10;
        }if (money>BCopter(1,1,player).getCost() && rand()%3==1){
            return 9;
        }
    }else if (AirType==false){
        if (money>NeoTank(1,1,player).getCost()&& ((rand()%2==1 && blinde)||(rand()%5==1))){
            return 8;
        }if (money>MegaTank(1,1,player).getCost() && rand()%2==1 && blinde){
            return 7;
        }if (money>MdTank(1,1,player).getCost()&& rand()%2==1 && blinde){
            return 6;
        }if (money>AntiAir(1,1,player).getCost()&& rand()%5==1 && air){
            return 4;
        }if (money>Tank(1,1,player).getCost() && rand()%2==1 ){
            return 5;
        }if (money>Recon(1,1,player).getCost()&& ((rand()%2==1 && blinde==false)||(rand()%4==0 && blinde))){
            return 3;

        }if (money>Bazooka(1,1,player).getCost() && rand()%2==0 && blinde){
            return 2;
        }if (money>Infantery(1,1,player).getCost()){
            return 1;
        }

    }
        std::cout<<"Erreur, le montant devrait permettre de créer une unité ci-dessus"<<std::endl;
        return 100;

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
//Retourne le bâtiment le plus proche qui ne soit pas capturé ou contrôlé par l'ennemi
Buildings* IA::closestBuilding(Unit* u){
    std::vector<Buildings*>* buildings = game->getBuildings();
    double minimumDistance=1000;
    Buildings* building = NULL;
    for(Buildings* b : *buildings){

        double distance = sqrt(pow(u->getPosX() - b->getPosX(),2)+pow(u->getPosY() - b->getPosY(),2));

        if (distance<minimumDistance && b->getOwner() != player && checkifobj(b)){ //vérifie si le batiment n'est pas contrôlé par le joueur et qu'il ne soit pas déjà un objectif
            minimumDistance=distance;
            building=b;
        }
    }
    if(building == NULL){
        for(Buildings* b : *buildings){//pour éviter de retourner un NULL si tous les batiment ssont déjà obj, temporaire

            double distance = sqrt(pow(u->getPosX() - b->getPosX(),2)+pow(u->getPosY() - b->getPosY(),2));

            if (distance<minimumDistance && b->getOwner() != player){ //vérifie si le batiment n'est pas contrôlé par le joueur et qu'il ne soit pas déjà un objectif
                minimumDistance=distance;
                building=b;
            }
        }
    }
    return building;

}
//Retourne l'unité ennemie la plus proche
Unit* IA::closestEnnemyUnit(Unit* u){ //WIP
    double minimumDistance=1000;

    Unit* closestunit = NULL;
    std::vector<Unit*>* units= game->getUnits();
    for(Unit* un : *units){

        if(un->getOwner() != player){
           double distance = sqrt(pow(u->getPosX() - un->getPosX(),2)+pow(u->getPosY() - un->getPosY(),2));
           std::cout<< u->getPosX() << " y " << u->getPosY() <<std::endl;
           if (distance<minimumDistance && niceattack(u,un) &&checkNobj(un)<=2){
               std::cout<<"U own OK " << distance << std::endl;
               minimumDistance=distance;
               closestunit = un;
            }
        }

    }
 return closestunit;
}


void IA::adobjunit(Unit* u){

    objunit.push_back(u);

}

void IA::adobjbuild(Buildings* b){
    std::cout<<"adobjbuild"<<std::endl;

    objbuild.push_back(b);

}

std::vector<Unit*> IA::getObjunit(){
    return objunit;
}

std::vector<Buildings*> IA::getObjbuild(){
    return objbuild;
}

void IA::resetObj(){
    objunit.clear();
    objbuild.clear();
}

bool IA::checkifobj(Buildings* build){

    std::vector<Buildings*> obj= getObjbuild();
        for(Buildings* b: obj ){
            if(build == b){

                return false;
            }
        }

    return true;
}
//retourne la position accessible la plus proche de l'objectif
std::pair<int,int> IA::getClosestAccessible(Unit* u, int x, int y){
    std::vector<std::pair<int,int>> move = game->getMoveCells(u);
    double min = 100;
    std::pair<int,int> wheretomove;
    for(std::pair<int,int> p: move){
        double dist = sqrt(pow(p.first - x,2) + pow(p.second - y ,2));
        if(dist<min && game->checkUnitOnPos(p.first,p.second) == false &&
                game->checkBuildingOnPos(p.first,p.second) == false ){
            min = dist;
            wheretomove = p;
        }
    }
    return wheretomove;
}
//vérifie si l'énnemi a des unités aériennes
bool IA::checkifair(){
    bool b = false;
    std::vector<Unit*>* units= game->getUnits();
    for(Unit* un : *units){
        if(un->getOwner() != player && ((un->getID()==11)||(un->getID()==10)||(un->getID()==9)) ){
            b = true ;

        }
    }
    return b;
}

bool IA::checkifblinde(){
    bool b = false;
    std::vector<Unit*>* units= game->getUnits();
    for(Unit* un : *units){
        if(un->getOwner() != player && ((un->getID()==5)||(un->getID()==6)||(un->getID()==7)) ){
            b = true ;
        }
    }
    return b;
}

bool IA::niceattack(Unit* a, Unit* v){
    int ida = a->getID();
    int idv = v->getID();
    if(ida!=10&&ida!=4 && (idv==10||idv==11)){
        return false;
    }
    if(ida==1&&idv!=1&&idv!=2&&idv!=3&&idv!=4&&idv!=9){
        return false;
    }
    if((ida==4||ida==10)&&idv!=9&&idv!=10&&idv!=11){
        return false;
    }
    if(ida==idv && a->getHealth() < v->getHealth()){
        return false;
    }

    std::cout<<"datniceattack"<<std::endl;
    return true;
}

int IA::checkNobj(Unit* u){
    int i = 0;
    std::vector<Unit*> obj = getObjunit();
    for(Unit* un : obj){
        if(u == un){i++;}
    }
    return i;
}
