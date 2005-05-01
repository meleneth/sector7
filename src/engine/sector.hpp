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
        Entity * setup_connecting(void);
        void dump(NetPacket *packet);
        std::string sector_id;
        int is_master;
        virtual Entity *add_entity (Entity * entity);

        Vector *position;
        Area *bound;

    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

#endif
