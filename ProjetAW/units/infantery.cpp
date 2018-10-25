#include "infantery.h"
#include <iostream>

Infantery::Infantery(int xi, int yi, Player* owner)
{
   this->owner = owner;
   health = 10;
   damage = 1;
   disp = 1;
   id = 1; // used for view
   x = xi;
   y = yi;
   std::pair<int,int> pos(x,y);
   std::pair<int,int> dir(0,1);
   std::cout << "Infantery created with position x y " << pos.first << " " << pos.second << std::endl;
}
