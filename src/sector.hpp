#ifndef ___sector_inc
#define ___sector_inc 1

#include"SDL.h"
#include"entitymgr.hpp"
#include<string>

class EntityMgr;

class Sector : public EntityMgr {
    public:
        // Public data members go here.
        Sector::Sector(std::string sector_id); // Constructor
        Sector::~Sector(); // Destructor
        
        void setup_master(void);
        void setup_connecting(void);
        
        std::string sector_id;
        int is_master;
    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

#endif
