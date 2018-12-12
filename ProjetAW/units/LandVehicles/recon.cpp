#include "recon.h"
#include <iostream>

Recon::Recon(int xi, int yi, Player* owner)
{
   this->owner = owner;
	this->name = "recon";
   health = 10;
   damage = 1;
   disp = 1;
   id = 3; // used for view
   x = xi;
   y = yi;
   oldX = 0;
   oldY = 0;
   canMove = false;
   canAttack = false;
   movementPoints = 8; // can be found here => http://awbw.amarriner.com/units.php
   movementType=4;
   cost=4000;
   std::pair<int,int> dir(0,1);
}
