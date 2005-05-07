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
        EntityMgr::EntityMgr(); // Constructor
        EntityMgr::~EntityMgr(); // Destructor
        Entity *_new_ent_of_type(Uint16 ent_type, Sint16 size);
        virtual Entity *add_entity(Entity *entity);
        Entity *ent_for_id(Uint32 id);
        void dump_all(void);

        virtual void remove_ent(Entity *entity);
        int frameupdate(void);
        virtual int render(void);

        Entity *chkCollision(Entity *check);
        Uint32 ent_id;
        
        std::list< Entity * > entities;
        Uint32 num_ents;

    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
