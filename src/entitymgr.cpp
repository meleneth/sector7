#include"stdutil.hpp"
#include"entitymgr.hpp"
#include"particles.hpp"
#include"engine.hpp"
#include"event.hpp"

#include<list>

// Public data members go here.
EntityMgr::EntityMgr ()		// Constructor
{
  ent_id = 0;
}

EntityMgr::~EntityMgr ()	// Destructor
{
}

Entity *
EntityMgr::add_entity (Entity * entity)
{
  entities.push_front (entity);

  ent_id++;
  entity->ent_id = ent_id;

  return entity;
}

int EntityMgr::frameupdate (void)
{
    std::list < Entity * >::iterator i;
    std::list < Entity *> dead_ents;
    static Uint32 spawn = 0;

    for (i = entities.begin (); i != entities.end (); ++i)
        if (!(*i)->frameupdate())
        {
            dead_ents.push_front(*i);
        }

    for (i = dead_ents.begin() ; i != dead_ents.end() ; ++i)
    {
        delete_events_for_ent(*i);
        remove_ent(*i);
    }
    return true;
}

void
EntityMgr::delete_events_for_ent (Entity *ent)
{
    std::list < Event *> dead_events;
    std::list < Event * >::iterator i;
    for (i = things_to_happen.begin() ; i != things_to_happen.end() ; ++i)
    {
        if(ent == (*i)->actor)
        {
            dead_events.push_front(*i);
        }
    }
    
    for (i = dead_events.begin() ; i != dead_events.end() ; ++i)
    {
        things_to_happen.remove(*i);
        delete *i;
    }
}

void
EntityMgr::remove_ent (Entity *ent)
{
        entities.remove(ent);
        ent->death();
        delete ent;
}

int
EntityMgr::render (void)
{
    std::list < Entity * >::iterator i;
  num_ents = 0;

  glColor4f (1, 1, 1, 1);

  for (i = entities.begin (); i != entities.end (); ++i)
    {
          (*i)->render ();
          num_ents++;
    }
  return true;
}

Entity *EntityMgr::chkCollision (Entity *check)
{
    std::list < Entity * >::iterator i;

  for (i = entities.begin (); i != entities.end (); ++i)
    {
      if ((*i)->chkCollision(check) == true)
	return *i;
    }
  return NULL;
}

void EntityMgr::add_event(Event *event)
{
    if (things_to_happen.size() == 0){
        things_to_happen.push_front(event);
    } else {
        std::list < Event * >::iterator i;
        for (i = things_to_happen.begin (); i != things_to_happen.end (); ++i)
        {
            if (((*i)->time_index + (*i)->time_offset) <= 
               (event->time_offset + event->time_index))
            {
                things_to_happen.insert(i, event);
                return;
            }
        }
    }
}

void EntityMgr::run_event(void)
{
    //run events from the list until you reach a time offset greater
    //than what was passed in    
    std::list < Event *> dead_events;
    std::list < Event * >::iterator i;
    for (i = things_to_happen.begin (); i != things_to_happen.end (); ++i)
    {
        if (game->framecount >= ((*i)->time_offset + (*i)->time_index))
        {
            (*i)->run();      
            if ((*i)->repeats) {
                Event *new_event = (*i)->clone();
                entmgr->add_event(new_event);
            }
            dead_events.push_front(*i);
        }
    }

    for (i = dead_events.begin() ; i != dead_events.end() ; ++i)
    {
        things_to_happen.remove(*i);
        delete *i;
    }
}

// Private members go here.

// Protected members go here.
