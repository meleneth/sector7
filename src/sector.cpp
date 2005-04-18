#include "sector.hpp"
#include "globals.hpp"

// Public data members go here.
Sector::Sector(std::string sector_id) // Constructor
{
    this->sector_id = sector_id;
    this->entmgr = new EntityMgr();
    is_master = 0;
    console->log("Sector " + sector_id + " created");
}
    
Sector::~Sector() // Destructor
{
}

int Sector::frameupdate(void)
{
    this->entmgr->frameupdate();
}

void Sector::setup_master(void)
{
    is_master = 1;
    console->log("Master sector initialized.");
}

// Private members go here.
// Protected members go here.
