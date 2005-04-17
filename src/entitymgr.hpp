/*Stop multiple inclusion */
#ifndef ___entitymgr_inc
#define ___entitymgr_inc 1

#include<list>

#include"SDL.h"

#include"entity.hpp"
#include"asteroid.hpp"
#include"titlescreen.hpp"
#include"event.hpp"


class EntityMgr {
    public:
        // Public data members go here.
        EntityMgr::EntityMgr(); // Constructor
        EntityMgr::~EntityMgr(); // Destructor
        Entity *_new_ent_of_type(Uint16 ent_type, Sint16 size);
        Entity *add_entity(Entity *entity);
        void remove_ent(Entity *entity);
        void delete_events_for_ent(Entity *entity);
        void run_event(void);
        void add_event(Event *event);
                 
        int frameupdate(void);
        int render(void);
        Entity *chkCollision(Entity *check);
        Uint32 ent_id;
        
        std::list< Entity * > entities;
        std::list< Event * > things_to_happen;
        Uint32 num_ents;

    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

extern EntityMgr *entmgr;
extern EntityMgr *bg_particles;
extern EntityMgr *fg_particles;

#endif
