#include "bazooka.h"
#include <iostream>

Bazooka::Bazooka(int xi, int yi, Player* owner)
{
   this->owner = owner;
	this->name = "bazooka";
   health = 10;
   damage = 1;
   disp = 1;
   id = 2; // used for view
   x = xi;
   y = yi;
   oldX = 0;
   oldY = 0;
   canMove = false;
   canAttack = false;
   movementPoints = 2; // can be found here => http://awbw.amarriner.com/units.php
   movementType=2;
   cost=3000;
   std::pair<int,int> dir(0,1);
}
