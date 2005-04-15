#include "stdutil.hpp"
#include "level.hpp"


// Public data members go here.
Level::Level(void) // Constructor
{
    framecount=0;
}

Level::~Level() // Destructor
{
}

void Level::frameupdate(void)
{
    framecount++;
}


// Private members go here.

// Protected members go here.
