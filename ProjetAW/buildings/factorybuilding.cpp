#include "factorybuilding.h"

FactoryBuilding::FactoryBuilding(int x, int y, int cellID)
{
	owner = nullptr;
	id = 1;
	posX = x;
	posY = y;
    cash = 1000;
	capturepoint = 20;
	cellId = cellID;
}
