#include"stdutil.hpp"
#include"entitymgr.hpp"
#include"particles.hpp"
#include"engine.hpp"

#include<list>

// Public data members go here.
EntityMgr::EntityMgr ()		// Constructor
{
}

EntityMgr::~EntityMgr ()	// Destructor
{
}

Entity *EntityMgr::add_entity (Entity * entity)
{
    entities.push_front(entity);
    return entity;
}

void EntityMgr::dump_all(void)
{
    std::list < Entity * >::iterator i;
    console->log("Entities:");

    for (i = entities.begin(); i != entities.end(); ++i)
        (*i)->log_info();

    console->log("---------");
}

int EntityMgr::frameupdate (void)
{
    std::list < Entity * >::iterator i;
    std::list < Entity *> dead_ents;
    std::stringstream buf;

    for (i = entities.begin(); i != entities.end(); ++i)
        if (!(*i)->frameupdate())
        {
            buf << "found dead ent " << (*i);
            console->log(buf.str());
            buf.str("");
            dead_ents.push_front(*i);
        }

    for (i = dead_ents.begin() ; i != dead_ents.end() ; ++i)
    {
            buf << "removing dead ent " << (*i);
            console->log(buf.str());
            buf.str("");
        remove_ent(*i);
    }
    return true;
}

int EntityMgr::frameupdate_with_collisions (void)
{
    std::list < Entity * >::iterator i;
    std::list < Entity *> dead_ents;

    for (i = entities.begin(); i != entities.end(); ++i)
    {
        chkCollision(*i);
        if (!(*i)->frameupdate())
        {
            dead_ents.push_front(*i);
        }
    }

    for (i = dead_ents.begin() ; i != dead_ents.end() ; ++i)
    {
        remove_ent(*i);
    }
    return true;
}

void EntityMgr::render (void)
{
    std::list < Entity * >::iterator i;
    num_ents = 0;

    glColor4f (1, 1, 1, 1);

    for (i = entities.begin (); i != entities.end (); ++i)
    {
          (*i)->render ();
          num_ents++;
    }
}

void EntityMgr::remove_ent (Entity *ent)
{
    entities.remove(ent);
    ent->death();
    delete ent;
}

Entity *EntityMgr::find_ent_for_id(Uint32 id)
{
    std::stringstream buf;
    std::list < Entity * >::iterator i;
    Entity *newEnt;

    for (i = entities.begin (); i != entities.end (); ++i) {
        if ((*i)->ent_id == id) return *i;
    }
    return NULL;
}

Entity *EntityMgr::ent_for_id(Uint32 id)
{
    Entity *newEnt = find_ent_for_id(id);

    if(newEnt)
        return newEnt;

    newEnt = new Entity();
    newEnt->ent_id = id;
    add_entity(newEnt);
    return newEnt;
}

Entity *EntityMgr::chkCollision (Entity *check)
{
    std::list < Entity * >::iterator i;
    for (i = entities.begin (); i != entities.end (); ++i){
        if (*i != check) {
            if (check->parent) {
                if (check->parent == (*i)) {
                    return NULL;
                }
            }
            if ((*i)->chkCollision(check) == true){
                std::stringstream buf;
                buf << "Collision! " << (*i) << " collided with " << check;
                console->log(buf.str());
                return *i;
            }
        }
    }
    return NULL;
}
// Private members go here.

// Protected members go here.
