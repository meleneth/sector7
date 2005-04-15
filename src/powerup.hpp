#include "stdutil.hpp"
#include"w_allinclude.hpp"
#include"soundcore.hpp"

#include"engine.hpp"



// Public data members go here.

PowerUp::PowerUp():Entity(E_POWERUP)	// Constructor
{
    texture = get_tex_id(TILE_SUPERPOWERUP);
    v->rotation = 0;
    collision_mask = E_PLAYER;
    health = 1;
}

PowerUp::~PowerUp()		// Destructor
{
}

int PowerUp::frameupdate()
{
    v->update_location();
    if(player1 && chkCollision(player1)){
        pickup(player1);
        return false;
    }
    return true;
}

void PowerUp::pickup(Player *player)
{
    // kiss kiss
    soundmgr->get_sound_id(POWERUP)
             ->play();
}

void PowerUp::render(void)
{

    static int delta = 0;
    Entity::render();
    size -=5;
    rotation += 180;
    rotation += delta++;
    Entity::render();
    size -=5;
    rotation -= (180.5+delta);
    Entity::render();
    size+=10;
    v->y++; 
}

// Private members go here.

// Protected members go here.
