#ifndef MAP_H
#define MAP_H

#include <string>
#include <fstream>
#include <vector>
#include "buildings/buildings.h"
#include "buildings/citybuilding.h"
#include "buildings/factorybuilding.h"
#include "buildings/airportbuilding.h"
#include "cell.h"


class Map
{
private:
    int sizeX;
    int sizeY;
    std::vector<int> split(const std::string& input, char delim);
    Cell getNewCell(int i,int j, int id);
    std::vector<std::vector<Cell>>* cells; // 2D Vector
	std::vector<Buildings*>* buildings; // We need to create the buildings here then the game will gather the vector
	// with a getter here
public:
    Map(std::string mapPath);
    int getSizeX();
    int getSizeY();
    Cell getCellAt(int x, int y);
	std::vector<std::vector<Cell>>* getCells();
	std::vector<Buildings*>* getBuildings();
};

#endif // MAP_H
