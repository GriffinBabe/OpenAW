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
    //Cell cells[static int sizeX][static int sizeY];
public:
    Map(std::string mapPath);
};

#endif // MAP_H
