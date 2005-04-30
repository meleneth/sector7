#ifndef ___weapon_inc
#define ___weapon_inc 1


#include"SDL.h"
#include "map_defines.hpp"
#include"entity.hpp"

class Weapon {
    public:
        Uint16 range;
        Sint16 damage;
        Uint16 firedelay;
        Entity *owner;
        Sint32 lastfire;

        Sint16 projectile_velocity;

        // Public data members go here.
        Weapon::Weapon(Entity *ownwer_ent); // Constructor
        virtual Weapon::~Weapon(); // Destructor

        virtual void fire_down();
        virtual void fire_up();
        virtual void fire_shot(RESTYPE x, RESTYPE y);
        virtual void render();
    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
