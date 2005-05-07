#include "stdutil.hpp"
#include "weapon.hpp"
#include<math.h>
#include"engine.hpp"

//extraneous comm3nt
Weapon::Weapon(Entity *owner_ent)	// Constructor
{
    range = 50;
    damage = 500;
    firedelay = 20;
    owner = owner_ent;
    lastfire=0;
}

Weapon::~Weapon()		// Destructor
{
}

void Weapon::frameupdate()
{
    if(lastfire){
        lastfire--;
    }
}

void Weapon::fire_down()
{
}

void Weapon::fire_up()
{
}

void Weapon::fire_shot()
{
//    Entity *shot = new Entity();
//    shot->v = target;
//    shot->texture = get_tex_id(TILE_LASER);
//    ((Sector *)owner->sector)->add_entity(shot);
}


void Weapon::render(void)
{
/*    glLoadIdentity();
    glTranslatef(x, y, 0);
    glRotatef(movement->angle, 0, 0, 1);
    texture->DrawGLSquare(16);
    return true;
    */
}


// Private members go here.

// Protected members go here.
