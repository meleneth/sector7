#include "stdutil.hpp"
#include "asteroid.hpp"
#include"map_defines.hpp"
#include"texture.hpp"
#include"sector.hpp"

#include<math.h>

#include"entitymgr.hpp"

TileNum asteroid_tile_map[] = {TILE_ROCK1, TILE_ROCK2, TILE_ROCK3, TILE_ROCK4, TILE_ROCK5, TILE_ROCK6};

// Public data members go here.
Asteroid::Asteroid(Uint16 mass)	// Constructor
{
    size = mass;
    setup_asteroid();
}

Asteroid::Asteroid(){
    size = rand() % 128;
    setup_asteroid();
}

Asteroid::Asteroid(Asteroid *parent, Uint16 mass)
{
    size = mass;
    setup_asteroid();
    v->set_from(parent->v);
    v->angle =  (rand() % 45) + 67;
    alignment = parent->alignment;
}

void Asteroid::setup_asteroid(void)
{
    if(size < 10)
        size = 12;
    health = size * 20;
    v->x = rand() % 200;
    v->y = rand() % 500;
    v->angle = (rand() % 45) + 67;
    v->power = 0; //rand() % 2+1;
    v->rotation = 3 - (rand() % 6);
    TileNum tex_id;
    tex_id = asteroid_tile_map[(rand() %6)];
    
    texture = get_tex_id(tex_id);
    experiance_value = 200;
    score_value = health * 4;
}

Asteroid::~Asteroid()		// Destructor
{
}

void Asteroid::death(void)
{
    Entity::death();
    Sint16 number = rand()%4+2;
    Sint16 ctr = number;
    if(health<0){
        // soundmgr->get_sound_id(SHOT_DESTROYED)
        //          ->play();
    }

    if(size>32){
        while(ctr--){
            ((Sector *)sector)->add_entity(new Asteroid(this, size));
        }
    }
}

int Asteroid::chkCollision(Entity *check)
{
    if(chkDeath())return 0; // No colliding with dead objects 
    
    if(Entity::chkCollision(check)){
        check->takeDamage(health, this);
        //soundmgr->get_sound_id(SHOT_HIT)
        //         ->play();
        return 1;
    }

    return 0;
}



// Private members go here.

// Protected members go here.
