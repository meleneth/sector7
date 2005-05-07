#include "stdutil.hpp"
#include"globals.hpp"
#include "w_plasmacannon.hpp"
#include "p_plasma.hpp"

#include"engine.hpp"



// Public data members go here.
PlasmaCannon::PlasmaCannon(Entity *owner_ent) : Weapon(owner_ent) // Constructor
{
    damage = 50;
    firedelay = 5;
    projectile_velocity = 1;
}

PlasmaCannon::~PlasmaCannon() // Destructor
{
}

int PlasmaCannon::frameupdate(){
    return true;
}

void PlasmaCannon::render(){
}

void PlasmaCannon::fire_shot(){
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
    Plasma *shot = new Plasma(damage, new_vec, owner);
    ((Sector *)(owner->sector))->add_entity(shot);
}

// Private members go here.

// Protected members go here.
