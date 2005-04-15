#include "stdutil.hpp"
#include"globals.hpp"
#include "w_lasercannon.hpp"
#include "p_laser.hpp"

#include"engine.hpp"



// Public data members go here.
LaserCannon::LaserCannon(Entity *owner_ent) : Weapon(owner_ent) // Constructor
{
    damage = 1000;
    firedelay = 10;
    projectile_velocity = 2;
}

LaserCannon::~LaserCannon() // Destructor
{
}

int LaserCannon::frameupdate(){
    return true;
}

void LaserCannon::render(){
}

void LaserCannon::fire_shot(RESTYPE x, RESTYPE y){
    if(!owner)
        return;
    static Sint32 last_fire = 0;
    
    if(last_fire>0){
        last_fire--;
        return;
    }else{
        last_fire = firedelay;
    }

    // x and y are the aiming points, only the owner can fire.
    Vector *new_vec = new Vector(owner->v);
    new_vec->power = projectile_velocity;
    new_vec->aim(x, y);
    new_vec->update_location();
    new_vec->update_location();
    Laser *shot = new Laser(damage, new_vec, owner);
    entmgr->add_entity(shot);
}

// Private members go here.

// Protected members go here.
