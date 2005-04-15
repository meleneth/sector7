#ifndef ___entitysquad_inc
#define ___entitysquad_inc 1

#include<list>

#include"SDL.h"
#include"entity.hpp"


class Entity;

class EntSquad {
    public:
        // Public data members go here.
        EntSquad::EntSquad(); // Constructor
        EntSquad::~EntSquad(); // Destructor

        void add_entity(Entity *entity);
        virtual void member_death(Entity *entity);
        virtual void last_member_killed(Entity *entity);
        
        int num_ents;

        std::list<Entity *> entities;
    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
