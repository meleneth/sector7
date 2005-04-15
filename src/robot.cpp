#include "stdutil.hpp"
#include "robot.hpp"
#include"map_defines.hpp"

#include"renderer.hpp"
#include<math.h>

#include"w_allinclude.hpp"
#include"powerup.hpp"


Robot::Robot():Entity(E_ENEMY)
{
    v->x = HALFXRES - (rand() % XRES);
    v->y = 0;

    v->angle = rand() % 3 + 90;
    v->rotation = 0;
    v->power = rand() % 2+1;
    texture = get_tex_id(TILE_ROBOT);
    health = 2500;
    experiance_value=20000;
    score_value=500;
    size  = 32;
    primary_weapon = new RocketLauncher(this);
    printf("Spawning ROBOT\n");
}

Robot::~Robot()		// Destructor
{
    delete primary_weapon;
}


int Robot::chkCollision(Entity *check){
    int result;

    result=Entity::chkCollision(check);

    if(result){
        takeDamage(95);
    }

    return result;
}


// Private members go here.

// Protected members go here.
