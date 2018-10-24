#ifndef MAP_H
#define MAP_H

#include <string>
#include <fstream>
#include <vector>
#include "cell.h"


class Map
{
private:
    int sizeX;
    int sizeY;
    std::vector<int> split(const std::string& input, char delim);
    Cell getNewCell(int i,int j, int id);
    std::vector<std::vector<Cell>>* cells; // 2D Vector
public:
    Map(std::string mapPath);
    int getSizeX();
    int getSizeY();
    Cell getCellAt(int x, int y);
};

#endif // MAP_H
