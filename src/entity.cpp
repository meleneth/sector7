#include "stdutil.hpp"
#include "entity.hpp"
#include "map_defines.hpp"

#include"renderer.hpp"
#include"soundcore.hpp"
#include"texture.hpp"
#include"engine.hpp"


#include"math.h"

// Public data members go here.
Entity::Entity() // Constructor
{
    setup_entity();
}

Entity::Entity(ENT_ALIGNMENT ent_alignment) // Constructor
{
    alignment = ent_alignment;
    collision_mask = alignment == E_PLAYER ? E_ENEMY : E_PLAYER;
    setup_entity();
}

Entity::~Entity() // Destructor
{
    delete v;
}

void Entity::setup_entity(void)
{
    v = new Vector();
    size=32;
    taken_damage = 0;
    texture = get_tex_id(TILE_NOTILE);
    health = 1;
    score_value = 0;
    experiance_value = 0;
    rotation=0;
}


void Entity::update_location(void){
    v->update_location();
    v->bounds_check();
    rotation += v->rotation;
}

int Entity::frameupdate(void){

	update_location();
    entmgr->chkCollision(this);
    return !chkDeath();
}

void Entity::render(void){
    glLoadIdentity();
    glTranslatef(v->x, v->y, 0);
    glRotatef(rotation, 0, 0, 1);
    if(taken_damage){
        glColor4f(1.0,0.0,0.0,1.0);
        texture->DrawGLSquare(size);
        glColor4f(1.0,1.0,1.0,1.0);
        taken_damage--;
    } else {
        texture->DrawGLSquare(size);
    }
}

int Entity::chkDeath(void){
    if((v->y > (YRES + 50)) || (v->y < -400)){
        return true;
    }
    if(health > 0)
        return false;
    return true;
}
	
int Entity::chkCollision(Entity *check)
{
    
    if(!(collision_mask & check->alignment))
        return false;
    
    if (abs( m_round(hypot(check->v->x - v->x, check->v->y - v->y))) < (size+check->size))
        return true;
    return false;
}

int Entity::takeDamage(Sint16 dmg)
{
    health -= dmg;
    taken_damage = 5;
    return true;
}

int Entity::takeDamage(Sint16 dmg, Entity *source)
{
    if(chkDeath()) return false;
    takeDamage(dmg);
    if(chkDeath()){
        source->has_killed(this);
        return false;
    }
    return true;
}

void Entity::has_killed(Entity *victim)
{
    // Does nothing by default
}

void Entity::death()
{

}

void Entity::kill_me_now(void)
{
    health=0;
}

// Private members go here.

// Protected members go here.
