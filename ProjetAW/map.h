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
public:
    Map(std::string mapPath);
    int getSizeX();
    int getSizeY();
};

#endif // MAP_H
