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
Mountain::Mountain(int x, int y, int id){
    posX = x;
    posY = y;
	type = id;
}
City::City(int x, int y, int id){
    posX = x;
    posY = y;
	type = id;
}

Factory::Factory(int x, int y, int id) {
	posX = x;
	posY = y;
	type = id;
}
Airport::Airport(int x, int y, int id){
    posX = x;
    posY = y;
    type = id;
}
Woods::Woods(int x, int y, int id){
    posX = x;
    posY = y;
	type = id;
}
River::River(int x, int y, int id){
    posX = x;
    posY = y;
	type = id;
}
Roads::Roads(int x, int y, int id){
    posX = x;
    posY = y;
	type = id;
}
Sea::Sea(int x, int y, int id){
    posX = x;
    posY = y;
	type = id;
}
Reefs::Reefs(int x, int y, int id){
    posX = x;
    posY = y;
	type = id;
}




