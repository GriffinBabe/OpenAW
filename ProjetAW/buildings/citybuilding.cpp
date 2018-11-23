#include "citybuilding.h"

CityBuilding::CityBuilding(int x, int y, int cellID)
{
	owner = nullptr;
	id = 2;
	posX = x;
	posY = y;
	cash = 1000;
	capturepoint = 20;
	cellId = cellID;
}
