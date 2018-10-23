#ifndef MAP_H
#define MAP_H

#include <string>
#include <fstream>
#include <vector>
#include "cell.h"


class map
{
private:
    int sizeX;
    int sizeY;
    std::vector<int> split(const std::string& input, char delim);
public:
    map(std::string mapPath);
};

#endif // MAP_H
