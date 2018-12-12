#include "tank.h"
#include <iostream>

Tank::Tank(int xi, int yi, Player* owner)
{
   this->owner = owner;
	this->name = "tank";
   health = 10;
   damage = 1;
   disp = 1;
   id = 5; // used for view
   x = xi;
   y = yi;
   oldX = 0;
   oldY = 0;
   canMove = false;
   canAttack = false;
   movementPoints = 6; // can be found here => http://awbw.amarriner.com/units.php
   movementType=4;
   cost=7000;
   std::pair<int,int> dir(0,1);
}

