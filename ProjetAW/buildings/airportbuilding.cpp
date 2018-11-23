#include "airportbuilding.h"

AirportBuilding::AirportBuilding(int x, int y, int cellID)
{
    owner = nullptr;
    id = 3;
    posX = x;
    posY = y;
    cash = 1000;
    capturepoint = 20;
	cellId = cellID;
}
