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
        Sector::Sector(std::string sector_id); // Constructor
        Sector::~Sector(); // Destructor
        
        void setup_master(void);
        Entity *setup_connecting(void);
        void dump(NetPacket *packet);
        std::string sector_id;
        int is_master;
        virtual Entity *add_entity (Entity * entity);
        void update_visible(void);

        Vector *position;
        Area *bound;
        std::list<Entity *> visible_entities;

        Sector *s_ne;
        Sector *s_nw;
        Sector *s_se;
        Sector *s_sw;

    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

#endif