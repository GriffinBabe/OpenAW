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

int Cell::getDefense()
{
	return defense;
}

int Cell::getMoveType()
{
    return moveType;
}

Pipe::Pipe(int x, int y, int id):Cell(x,y,id){
	defense = 0;
    moveType=6;
}
Grass::Grass(int x, int y, int id):Cell(x,y,id){
	defense = 1;
    moveType=1;
}
Mountain::Mountain(int x, int y, int id):Cell(x,y,id){
	defense = 4;
    moveType=2;
}
City::City(int x, int y, int id):Cell(x,y,id){
	defense = 3;
    moveType=4;
}
Factory::Factory(int x, int y, int id):Cell(x,y,id) {

    defense = 3;
    moveType=4;
}
Airport::Airport(int x, int y, int id):Cell(x,y,id){
	defense = 3;
    moveType=4;
}
Woods::Woods(int x, int y, int id):Cell(x,y,id){
	defense = 2;
    moveType=3;
}
River::River(int x, int y, int id):Cell(x,y,id){
	defense = 0;
    moveType=2;
}
Roads::Roads(int x, int y, int id):Cell(x,y,id){
	defense = 0;
    moveType=4;
}
Sea::Sea(int x, int y, int id):Cell(x,y,id){
	defense = 0;
    moveType=5;
}
Reefs::Reefs(int x, int y, int id):Cell(x,y,id){
	defense = 1;
    moveType=5;
}

Bridge::Bridge(int x, int y, int id):Cell(x,y,id)
{
	defense = 0;
	moveType = 4;
}
