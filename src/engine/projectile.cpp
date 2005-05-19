#include "stdutil.hpp"
#include "projectile.hpp"


// Public data members go here.
Projectile::Projectile(Sint16 dmg, Vector *direction, Entity *firing_party) // Constructor
{
    health = dmg;
    delete v;
    v=direction;
    taken_damage = 0;
    who_held_the_gun = firing_party;
    lifespan = 300;
    v->rotation = 0;
    parent = firing_party;

    log_info();
}

Projectile::~Projectile() // Destructor
{
}

int Projectile::frameupdate(void)
{
    lifespan--;
    if(lifespan == 0) 
        kill_me_now();
    return Entity::frameupdate();
}

int Projectile::chkCollision(Entity *check)
{
    if(who_held_the_gun != check)
    if(Entity::chkCollision(check)){
        check->takeDamage(health, who_held_the_gun);
        health = 0;
        return 1;
    }
    return 0;

}

void Projectile::log_info()
{
    std::stringstream buf;
    buf << this << "'s who_held is " << who_held_the_gun;
    console->log(buf.str());
    Entity::log_info();
}

// Private members go here.

// Protected members go here.
