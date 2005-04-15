#include "stdutil.hpp"
#include "w_scatterplasma.hpp"
#include"p_plasma.hpp"

#include"engine.hpp"


// Public data members go here.
ScatterPlasma::ScatterPlasma(Entity *owner_ent):PlasmaCannon(owner_ent) // Constructor
{

	damage=150;
	firedelay=1;
    lastfire=1;
    angdir=20;
    angoffset=0;
}

ScatterPlasma::~ScatterPlasma() // Destructor
{
}

void ScatterPlasma::fire_shot(RESTYPE x, RESTYPE y){
    if(!owner)
        return;

    
    if(lastfire){
        lastfire--;
        return;
    }else{
        lastfire = firedelay;
    }

	angoffset+=angdir;
	if(abs(angoffset)>32)
		angdir=-angdir;

    // x and y are the aiming points, only the owner can fire.
    Vector *new_vec = new Vector(owner->v);
    new_vec->power = projectile_velocity;
    new_vec->aim(x, y);
    new_vec->angle += angoffset;
    Plasma *shot = new Plasma(damage, new_vec, owner);
    entmgr->add_entity(shot);
}

// Private members go here.

// Protected members go here.
