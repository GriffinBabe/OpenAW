#include "bomber.h"
#include <iostream>

Bomber::Bomber(int xi, int yi, Player* owner)
{
   this->owner = owner;
   health = 10;
   damage = 1;
   disp = 1;
   id = 11; // used for view
   x = xi;
   y = yi;
   canMove = false;
   canAttack = false;
   movementPoints = 7; // can be found here => http://awbw.amarriner.com/units.php
   cost=22000;
   std::pair<int,int> dir(0,1);
}
