#include "mdtank.h"
#include <iostream>

MdTank::MdTank(int xi, int yi, Player* owner)
{
   this->owner = owner;
	this->name = "mdtank";
   health = 10;
   damage = 1;
   disp = 1;
   id = 6; // used for view
   x = xi;
   y = yi;
   oldX = 0;
   oldY = 0;
   canMove = false;
   canAttack = false;
   movementPoints = 5; // can be found here => http://awbw.amarriner.com/units.php
   movementType=4;
   cost=16000;
   std::pair<int,int> dir(0,1);
}

