#include "stdutil.hpp"
#include "weapon.hpp"
#include<math.h>
#include"engine.hpp"


Weapon::Weapon(Entity *owner_ent)	// Constructor
{
    range = 50;
    damage = 500;
    firedelay = 20;
    owner = owner_ent;
}

Weapon::~Weapon()		// Destructor
{
}

void Weapon::fire_down()
{
}

void Weapon::fire_up()
{
}

void Weapon::fire_shot(RESTYPE x, RESTYPE y)
{

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
