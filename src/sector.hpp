#ifndef ___sector_inc
#define ___sector_inc 1

#include"SDL.h"
#include"entitymgr.hpp"
#include<string>

class Sector {
    public:
        // Public data members go here.
        Sector::Sector(std::string sector_id); // Constructor
        Sector::~Sector(); // Destructor
        
        int frameupdate(void);
        void setup_master(void);
        
        EntityMgr *entmgr;
        std::string sector_id;
    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

#endif
