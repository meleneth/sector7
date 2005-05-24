#include "stdutil.hpp"
#include "entity.hpp"
#include "map_defines.hpp"

#include"renderer.hpp"
#include"texture.hpp"
#include"engine.hpp"
#include"sector.hpp"
#include"globals.hpp"

#include"math.h"

#define SIGNED_OFFSET 100000

// Public data members go here.
Entity::Entity() // Constructor
{
    std::stringstream buf;
    buf << "Entity at " << this << " created.";
    console->log(buf.str());
    setup_entity();
}

Entity::~Entity() // Destructor
{
    delete v;
}

void Entity::setup_entity(void)
{
    ent_id = 0;
    v = new Vector();
    sector = NULL;
    size=32;
    taken_damage = 0;
    texture = get_tex_id(TILE_NOTILE);
    health = 100;
    score_value = 0;
    experiance_value = 0;
    rotation=0;
    primary = NULL;
    parent = NULL;
}

void Entity::update_location(void){
    v->update_location();

    if(sector){
//        ((Sector *)sector)->bound->wrap_within(v);
    }
    rotation += v->rotation;
}

int Entity::frameupdate(void){

	update_location();

    if(primary){
        primary->frameupdate();
    }

    return !chkDeath();
}

void Entity::render(void){
    glLoadIdentity();
    glTranslatef(v->x, v->y, 0);
    glRotatef(v->angle+90, 0, 0, 1);
    if(taken_damage){
        glColor4f(1.0,0.0,0.0,1.0);
        texture->DrawGLSquare(size);
        glColor4f(1.0,1.0,1.0,1.0);
        taken_damage--;
    } else {
        texture->DrawGLSquare(size);
    }
}

void Entity::render(Vector *offset){
    glLoadIdentity();
    glTranslatef(offset->x - v->x, offset->y - v->y, 0);
    glRotatef(v->angle+90, 0, 0, 1);
    if(taken_damage){
        glColor4f(1.0,0.0,0.0,1.0);
        texture->DrawGLSquare(size);
        glColor4f(1.0,1.0,1.0,1.0);
        taken_damage--;
    } else {
        texture->DrawGLSquare(size);
    }
}

void Entity::move(Sint32 xdir, Sint32 ydir)
{
    v->x+=xdir;
    v->y+=ydir;
}

int Entity::chkDeath(void){
    if(health > 0)
        return false;
    return true;
}
	
int Entity::chkCollision(Entity *check)
{
    if(alignment == check->alignment) 
        return false;
    if (abs( m_round(hypot(check->v->x - v->x, check->v->y - v->y))) < (size+check->size)){
        check->takeDamage(health, this);
        return true;
    }
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
    std::stringstream buf;
    buf << "Entity died: " << this << " ent_id was " << ent_id;
    console->log(buf.str());
    buf.str("");
}

void Entity::kill_me_now(void)
{
    health=0;
}


void Entity::inflateLoc(EntLoc *newLoc)
{
   
    v->x        = (double) ntohl(newLoc->x) - SIGNED_OFFSET;
    v->y        = (double) ntohl(newLoc->y) - SIGNED_OFFSET;
    v->angle    = (double) ntohl(newLoc->angle) - SIGNED_OFFSET;
    v->power    = (double) ntohl(newLoc->power) - SIGNED_OFFSET;
    v->rotation = (double) ntohl(newLoc->rotation) - SIGNED_OFFSET;
}     

void Entity::inflateFull(EntFull *newFull)
{
    v->x        = (double) ntohl(newFull->x) - SIGNED_OFFSET;
    v->y        = (double) ntohl(newFull->y) - SIGNED_OFFSET;
    v->angle    = (double) ntohl(newFull->angle) - SIGNED_OFFSET;
    v->power    = (double) ntohl(newFull->power) - SIGNED_OFFSET;
    v->rotation = (double) ntohl(newFull->rotation) - SIGNED_OFFSET;
    size        = newFull->size;
    texture     = get_tex_id((TileNum) ntohl(newFull->textureID));
}

void Entity::deflateLoc(EntLoc *currentLoc)
{
    currentLoc->entID    = htonl(ent_id);
    currentLoc->x        = htonl(SIGNED_OFFSET + (Sint32) floor(v->x));
    currentLoc->y        = htonl(SIGNED_OFFSET + (Sint32) floor(v->y));
    currentLoc->angle    = htonl(SIGNED_OFFSET + (Sint32) floor(v->angle));
    currentLoc->power    = htonl(SIGNED_OFFSET + (Sint32) floor(v->power));
    currentLoc->rotation = htonl(SIGNED_OFFSET + (Sint32) floor(v->rotation));
}

void Entity::deflateFull(EntFull *currentFull)
{
    currentFull->entID = htonl(ent_id);
    currentFull->x         = htonl(SIGNED_OFFSET + (Sint32) floor(v->x));
    currentFull->y         = htonl(SIGNED_OFFSET + (Sint32) floor(v->y));
    currentFull->angle     = htonl(SIGNED_OFFSET + (Sint32) floor(v->angle));
    currentFull->power     = htonl(SIGNED_OFFSET + (Sint32) floor(v->power));
    currentFull->rotation  = htonl(SIGNED_OFFSET + (Sint32) floor(v->rotation));
    currentFull->textureID = htonl(texture->tilenum);
    currentFull->size      = size;
}

void Entity::log_info(void){
    std::stringstream buf;
    buf << "Entity [" << ent_id << "] Info: ";
    buf << "x: " << v->x << " y: " << v->y << " size: " << (int) size << " tid: " << (int)texture->tilenum;
    buf << " health: " << health;
    if(sector){
    buf << " sector: " << ((Sector *)sector)->sector_id;
    }
    console->log(buf.str());
}

// Private members go here.

// Protected members go here.
