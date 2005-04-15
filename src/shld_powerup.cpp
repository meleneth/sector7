#include "stdutil.hpp"
#include "shld_powerup.hpp"
#include"map_defines.hpp"

#include"renderer.hpp"


// Public data members go here.
ShieldPowerup::ShieldPowerup() : Entity(E_ENEMY)     // Constructor
{
    texture = get_tex_id(TILE_SHIELD);
    v->rotation = 0;
    health = 1;
}

ShieldPowerup::~ShieldPowerup()             // Destructor
{
}

int ShieldPowerup::chkCollision(Entity *check)
{
    if(!(check->alignment && E_PLAYER))
        return false;

    if(Entity::chkCollision(check)){
        // check->shielded = true;
        check->texture = get_tex_id(TILE_SHIPSHIELD);
        return true;
    }
    return false;
}


// Private members go here.


int ShieldPowerup::chkDeath(void)
{
    return 1;
}



// Private members go here.

// Protected members go here.
