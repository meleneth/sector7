#ifndef ___weapon_inc
#define ___weapon_inc 1


#include"SDL.h"
#include "map_defines.hpp"
#include"entity.hpp"

class Entity;
class Weapon {
    public:
        Uint16 range;
        Sint16 damage;
        Uint16 firedelay;
        Entity *owner;
        Sint32 lastfire;

        Sint16 projectile_velocity;

        // Public data members go here.
        Weapon(Entity *owner_ent); // Constructor
        virtual ~Weapon(); // Destructor
        
        virtual void frameupdate(void);
        virtual void fire_down();
        virtual void fire_up();
        virtual void fire_shot();
        virtual void render();
    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
