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

Pipe::Pipe(int x, int y, int id):Cell(x,y,id){
	defense = 0;
}
Grass::Grass(int x, int y, int id):Cell(x,y,id){
	defense = 1;
}
Mountain::Mountain(int x, int y, int id):Cell(x,y,id){
	defense = 4;
}
City::City(int x, int y, int id):Cell(x,y,id){
	defense = 3;
}
Factory::Factory(int x, int y, int id):Cell(x,y,id) {
	defense = 3;
}
Airport::Airport(int x, int y, int id):Cell(x,y,id){
	defense = 3;
}
Woods::Woods(int x, int y, int id):Cell(x,y,id){
	defense = 2;
}
River::River(int x, int y, int id):Cell(x,y,id){
	defense = 0;
}
Roads::Roads(int x, int y, int id):Cell(x,y,id){
	defense = 0;
}
Sea::Sea(int x, int y, int id):Cell(x,y,id){
	defense = 0;
}
Reefs::Reefs(int x, int y, int id):Cell(x,y,id){
	defense = 1;
}




