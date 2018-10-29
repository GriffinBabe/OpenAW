#ifndef CITY_H
#define CITY_H

#include "buildings/buildings.h"

class CityBuilding : public Buildings // renamed from "city" to "citybuilding" because of a cell with the same name
{
public:
	CityBuilding(int x,int y);
};

#endif // CITY_H
