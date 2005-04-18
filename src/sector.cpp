#include "sector.hpp"

// Public data members go here.
Sector::Sector(std::string sector_id) // Constructor
{
    this->sector_id = sector_id;
    this->entmgr = new EntityMgr();
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
}

// Private members go here.
// Protected members go here.
