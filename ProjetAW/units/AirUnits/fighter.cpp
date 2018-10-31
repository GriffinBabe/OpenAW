#include "fighter.h"
#include <iostream>

Fighter::Fighter(int xi, int yi, Player* owner)
{
   this->owner = owner;
   health = 10;
   damage = 1;
   disp = 1;
   id = 10; // used for view
   x = xi;
   y = yi;
   canMove = true; // Should be false, but let true until player's turns are implemented
   canAttack = false;
   movementPoints = 9; // can be found here => http://awbw.amarriner.com/units.php
   movementType=5;
   cost=20000;
   std::pair<int,int> dir(0,1);
}

