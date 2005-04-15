#ifndef ___event_inc
#define ___event_inc 1

#include"SDL.h"
#include"entity.hpp"

class Event {
    public:
        Event::Event(int time_index, void (Entity::*ptr_func)(void), Entity *actor, bool repeats);
        Event::Event(int time_index, Entity *actor, bool repeats);
        Event::~Event();
        void   (Entity::*ptr_func)(void);
        virtual void run(void);
        virtual Event *clone(void);
        bool   repeats;
        int    time_index;
        int time_offset;
        Entity *actor;
    private:
    protected:
}; 


#endif
