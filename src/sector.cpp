#include "sector.hpp"
#include "globals.hpp"

// Public data members go here.
Sector::Sector(std::string sector_id) // Constructor
{
    this->sector_id = sector_id;
    is_master = 0;
    console->log("Sector " + sector_id + " created");
}
    
Sector::~Sector() // Destructor
{
}

void Sector::setup_master(void)
{
    is_master = 1;
    console->log("Master sector initialized.");

    Entity *ship;

    ship = new Entity();
    ship->v->set_from_screen_coords(400, 200);
    ship->size = 32;
    ship->texture = get_tex_id(TILE_SHIP);
	ship->sector = this;
    add_entity(ship);
	
    ship = new Entity();
    ship->v->set_from_screen_coords(320, 200);
    ship->size = 32;
    ship->texture = get_tex_id(TILE_SHIP);
	ship->sector = this;
    add_entity(ship);
}

void Sector::setup_connecting(void)
{
    Entity *ship;

    ship = new Entity();
    ship->v->set_from_screen_coords(320, 200);
    ship->size = 128;
    ship->texture = get_tex_id(TILE_SHIP);
	ship->sector = this;
    add_entity(ship);
}

// Private members go here.
// Protected members go here.
