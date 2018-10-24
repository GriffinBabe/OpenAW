#include "cell.h"

Cell::Cell(){

}
Cell::Cell(int x,int y, int id)
{
    posX = x;
    posY= y;
    type=id;

}
int Cell::gettype(){
    return type;
}
void Cell::settype(int t){
    type = t;
}
void Cell::setPos(int x,int y){
    posX=x;
    posY=y;
}
int Cell::getPosX(){
    return posX;
}
int Cell::getPosY(){
    return posY;
}

Pipe::Pipe(int x, int y, int id){
    posX = x;
    posY = y;
    type = id;
}

Grass::Grass(int x, int y, int id){
    posX = x;
    posY = y;
    type = id;
}

