#ifndef ___w_lasercannon_inc
#define ___w_lasercannon_inc 1

#include"weapon.hpp"
#include"entity.hpp"
#include"SDL.h"

#include<math.h>

class LaserCannon : public Weapon {
    public:
        // Public data members go here.
        LaserCannon::LaserCannon(Entity *owner_ent); // Constructor
        LaserCannon::~LaserCannon(); // Destructor

        virtual int frameupdate();
        virtual void render();
        virtual void fire_shot(RESTYPE x, RESTYPE y);
    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
