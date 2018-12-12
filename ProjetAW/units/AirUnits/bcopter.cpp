#include "bcopter.h"
#include <iostream>

BCopter::BCopter(int xi, int yi, Player* owner)
{
	this->owner = owner;
	this->name = "bcopter";
   health = 10;
   damage = 1;
   disp = 1;
   id = 9; // used for view
   x = xi;
   y = yi;
   oldX = 0;
   oldY = 0;
   canMove = false;
   canAttack = false;
   movementPoints = 6; // can be found here => http://awbw.amarriner.com/units.php
   movementType=5; //Type Air
   cost=9000;
   std::pair<int,int> dir(0,1);
}
