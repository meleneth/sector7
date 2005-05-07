#include "stdutil.hpp"
#include"globals.hpp"
#include "w_plasmacannon.hpp"
#include "p_plasma.hpp"

#include"engine.hpp"



// Public data members go here.
PlasmaCannon::PlasmaCannon(Entity *owner_ent) : Weapon(owner_ent) // Constructor
{
    damage = 50;
    firedelay = 6;
    projectile_velocity = 1;
    lastfire = 0;
}

PlasmaCannon::~PlasmaCannon() // Destructor
{
}

void PlasmaCannon::render(){
}

void PlasmaCannon::fire_shot(){
    if(!owner)
        return;

    if(lastfire>0)
        return;
    
    lastfire = firedelay;
    Vector *new_vec = new Vector(owner->v);
    new_vec->power = projectile_velocity;
    Plasma *shot = new Plasma(damage, new_vec, owner);
    ((Sector *)(owner->sector))->add_entity(shot);
}

// Private members go here.

// Protected members go here.
