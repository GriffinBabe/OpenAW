#ifndef AIRPORT_H
#define AIRPORT_H
#include "buildings/buildings.h"

class AirportBuilding : public Buildings // renamed from "airport" to "airportbuilding" because of a cell with the same name
{
public:
    AirportBuilding(int x, int y);
};

#endif // AIRPORT_H
