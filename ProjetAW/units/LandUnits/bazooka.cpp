#include "bazooka.h"
#include <iostream>

Bazooka::Bazooka(int xi, int yi, Player* owner)
{
   this->owner = owner;
   health = 10;
   damage = 1;
   disp = 1;
   id = 2; // used for view
   x = xi;
   y = yi;
   canMove = true; // Should be false, but let true until player's turns are implemented
   canAttack = false;
   movementPoints = 2; // can be found here => http://awbw.amarriner.com/units.php
   cost=3000;
   std::pair<int,int> dir(0,1);
}
