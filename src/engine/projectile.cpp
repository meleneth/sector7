#include "stdutil.hpp"
#include "projectile.hpp"


// Public data members go here.
Projectile::Projectile(Sint16 dmg, Vector *direction, Entity *firing_party) // Constructor
{
    alignment = firing_party->alignment;
    collision_mask = alignment == E_PLAYER 
                    ? E_ENEMY 
                    : E_PLAYER;
    health = dmg;
    delete v;
    v=direction;
    taken_damage = 0;
    who_held_the_gun = firing_party;
    lifespan = 300;
    v->rotation = 0;
}

Projectile::Projectile(Projectile *source)
{
    alignment = source->alignment;
    collision_mask = source->collision_mask;
    health = source->health;
    taken_damage = 0;
    who_held_the_gun = source->who_held_the_gun;
    lifespan = source->lifespan;
    v->set_from(source->v);
}

Projectile::~Projectile() // Destructor
{
}

int Projectile::frameupdate(void)
{
    lifespan--;
    if(lifespan == 0) 
        health = 0;
    return Entity::frameupdate();
}

int Projectile::chkCollision(Entity *check)
{
    if(who_held_the_gun->ent_id != check->ent_id)
    if(Entity::chkCollision(check)){
        check->takeDamage(health, who_held_the_gun);
        health = 0;
        return 1;
    }
    return 0;

}

// Private members go here.

// Protected members go here.
