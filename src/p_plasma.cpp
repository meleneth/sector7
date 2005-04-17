#include "stdutil.hpp"
#include "p_plasma.hpp"
#include"entity.hpp"


// Public data members go here.
Plasma::Plasma(Sint16 dmg, Vector *direction, Entity *firing_party):Projectile(dmg, direction, firing_party) // Constructor
{
    size = 10;
    texture = get_tex_id(TILE_BEAMW);
    v->rotation = 5; 
}

Plasma::~Plasma() // Destructor
{

}


// Private members go here.

// Protected members go here.
