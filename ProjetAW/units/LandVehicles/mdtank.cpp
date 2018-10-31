#include "mdtank.h"
#include <iostream>

MdTank::MdTank(int xi, int yi, Player* owner)
{
   this->owner = owner;
   health = 10;
   damage = 1;
   disp = 1;
   id = 6; // used for view
   x = xi;
   y = yi;
   canMove = false;
   canAttack = false;
   movementPoints = 5; // can be found here => http://awbw.amarriner.com/units.php
   cost=16000;
   std::pair<int,int> dir(0,1);
}

