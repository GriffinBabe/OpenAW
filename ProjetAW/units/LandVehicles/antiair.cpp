#include "antiair.h"
#include <iostream>

AntiAir::AntiAir(int xi, int yi, Player* owner)
{
   this->owner = owner;
   health = 10;
   damage = 1;
   disp = 1;
   id = 4; // used for view
   x = xi;
   y = yi;
   canMove = false;
   canAttack = false;
   movementPoints = 6; // can be found here => http://awbw.amarriner.com/units.php
   cost=8000;
   std::pair<int,int> dir(0,1);
}
