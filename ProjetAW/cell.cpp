#include "cell.h"

Cell::Cell(){

}
Cell::Cell(int pX,int pY,int t)
{
    posX= pX;
    posY=pY;
    type=t;

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
