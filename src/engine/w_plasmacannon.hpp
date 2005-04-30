#ifndef ___w_plasmacannon_inc
#define ___w_plasmacannon_inc 1

#include"weapon.hpp"
#include"entity.hpp"
#include"SDL.h"

#include<math.h>

class PlasmaCannon : public Weapon {
    public:
        // Public data members go here.
        PlasmaCannon::PlasmaCannon(Entity *owner_ent); // Constructor
        PlasmaCannon::~PlasmaCannon(); // Destructor

        virtual int frameupdate();
        virtual void render();
        virtual void fire_shot(RESTYPE x, RESTYPE y);
    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
