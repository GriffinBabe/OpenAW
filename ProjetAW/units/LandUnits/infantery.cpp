#include "infantery.h"
#include <iostream>

Infantery::Infantery(int xi, int yi, Player* owner)
{
   this->owner = owner;
	this->name = "infantery";
   health = 10;
   damage = 1;
   disp = 1;
   id = 1; // used for view
   x = xi;
   y = yi;
   canMove = false;
   canAttack = false;
   movementPoints = 3; // can be found here => http://awbw.amarriner.com/units.php
   movementType=1;
   cost=1000;
   std::pair<int,int> dir(0,1);
}
