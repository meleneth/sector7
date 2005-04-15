#include "stdutil.hpp"
#include"globals.hpp"
#include "w_rocketlauncher.hpp"
#include "p_rocket.hpp"

#include"engine.hpp"

// Public data members go here.
RocketLauncher::RocketLauncher(Entity *owner_ent) : Weapon(owner_ent) // Constructor
{
    damage = 1500;
    firedelay = 30;
    projectile_velocity = -3;
}

RocketLauncher::~RocketLauncher() // Destructor
{
}

int RocketLauncher::frameupdate(){
    return true;
}

void RocketLauncher::render(){
}

void RocketLauncher::fire_shot(RESTYPE x, RESTYPE y){
    if(!owner)
        return;

    static Sint32 last_fire = game->framecount;
    
    if(last_fire > game->framecount){
        return;
    }else{
        last_fire = game->framecount + firedelay;
    }

    Sint32 offset = 20 + rand() % 10;

    // x and y are the aiming points, only the owner can fire.
    Vector *new_vec = new Vector(owner->v);
    new_vec->power = projectile_velocity;
    new_vec->aim(x, y);
    new_vec->angle -= offset;
    Rocket *shot = new Rocket(damage, new_vec, owner);
    entmgr->add_entity(shot);

    new_vec = new Vector(owner->v);
    new_vec->power = projectile_velocity;
    new_vec->aim(x, y);
    new_vec->angle += offset;
    shot = new Rocket(damage, new_vec, owner);
    entmgr->add_entity(shot);

    new_vec = new Vector(owner->v);
    new_vec->power = projectile_velocity;
    new_vec->aim(x, y);
    shot = new Rocket(damage, new_vec, owner);
    entmgr->add_entity(shot);
}

// Private members go here.

// Protected members go here.
