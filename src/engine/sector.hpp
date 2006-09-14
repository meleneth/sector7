#ifndef ___sector_inc
#define ___sector_inc 1

#include"SDL.h"
#include"entitymgr.hpp"
#include"netserverclient.hpp"
#include<string>
#include"area.hpp"

class EntityMgr;

class Sector : public EntityMgr {
    public:
        // Public data members go here.
        Sector(std::string sector_id); // Constructor
        ~Sector(); // Destructor
        
        void setup_master(void);
        Entity *setup_connecting(void);
        std::string sector_id;
        int is_master;
        virtual Entity *add_entity (Entity * entity);
        virtual void remove_ent(Entity *entity);
        void update_visible(void);
        virtual void attach_sector(Sector *sector);
        void detach_sector(Sector *sector);
        virtual void render(void);
        void list_ents(void);
        
        Vector *position;
        Area *bound;
        std::list<Entity *> visible_entities;
        std::list<Sector *> attached_sectors;

    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

#endif
