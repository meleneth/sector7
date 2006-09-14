#ifndef ___w_plasmacannon_inc
#define ___w_plasmacannon_inc 1

#include"weapon.hpp"
#include"entity.hpp"
#include"SDL.h"

#include<math.h>

class PlasmaCannon : public Weapon {
    public:
        // Public data members go here.
        PlasmaCannon(Entity *owner_ent); // Constructor
        ~PlasmaCannon(); // Destructor

        virtual void render();
        virtual void fire_shot();
    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
