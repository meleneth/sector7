#include "stdutil.hpp"
#include "physics.hpp"


// Public data members go here.
Physics::Physics ()		// Constructor
{
//Arbitrary "default" values
  topspeed = 50;
  accelerationrate = 2;
  momentum = -1;
  turnrate = 3;
}

Physics::~Physics ()		// Destructor
{
}

Sint16 Physics::howfast (int accelerating)
{
  if (accelerating)
    {
//      printf("I am accelerating%d\n",accelerating);
      return accelerationrate;
    }
  return momentum;
}

Sint16 Physics::getturnrate ()
{
  return turnrate;
}

// Private members go here.

// Protected members go here.
