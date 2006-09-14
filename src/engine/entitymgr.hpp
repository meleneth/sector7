/*Stop multiple inclusion */
#ifndef ___entitymgr_inc
#define ___entitymgr_inc 1

#include<list>

#include"SDL.h"

#include"entity.hpp"

class Entity;

class EntityMgr {
    public:
        // Public data members go here.
        EntityMgr(); // Constructor
        ~EntityMgr(); // Destructor
        Entity *_new_ent_of_type(Uint16 ent_type, Sint16 size);
        virtual Entity *add_entity(Entity *entity);
        Entity *find_ent_for_id(Uint32 id);
        Entity *ent_for_id(Uint32 id);
        void dump_all(void);
        int frameupdate_with_collisions (void);

        virtual void remove_ent(Entity *entity);
        int frameupdate(void);
        virtual void render(void);

        Entity *chkCollision(Entity *check);
        
        std::list< Entity * > entities;
        Uint32 num_ents;

    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
