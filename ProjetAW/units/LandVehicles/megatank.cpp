#include "megatank.h"
#include <iostream>

MegaTank::MegaTank(int xi, int yi, Player* owner)
{
   this->owner = owner;
   health = 10;
   damage = 1;
   disp = 1;
   id = 7; // used for view
   x = xi;
   y = yi;
   canMove = false;
   canAttack = false;
   movementPoints = 4; // can be found here => http://awbw.amarriner.com/units.php
   movementType=4;
   cost=28000;
   std::pair<int,int> dir(0,1);
}

