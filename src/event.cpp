#include "stdutil.hpp"
#include"game.hpp"
#include "event.hpp"
#include"engine.hpp"

Event::Event(int time_index, void (Entity::*ptr_func)(void), Entity *actor, bool repeats)
{
    this->time_index = time_index;
    this->time_offset = game->framecount;
    this->ptr_func = ptr_func;
    this->actor = actor;
    this->repeats = repeats;
}

Event::Event(int time_index, Entity *actor, bool repeats)
{
    this->time_index = time_index;
    this->ptr_func = NULL;
    this->actor = actor;
    this->repeats = repeats;
    this->time_offset = game->framecount;

}

Event::~Event() // Destructor
{
}

void Event::run(void)
{
    if(ptr_func){
        (actor->*ptr_func)();
    }
}

Event *Event::clone(void)
{
    return new Event(time_index, ptr_func, actor, repeats);
}


// Private members go here.

// Protected members go here.
