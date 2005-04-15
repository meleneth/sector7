#ifndef ___w_rocketlauncher_inc
#define ___w_rocketlauncher_inc 1

#include"weapon.hpp"
#include"entity.hpp"
#include"SDL.h"

#include<math.h>

class RocketLauncher : public Weapon {
    public:
        // Public data members go here.
        RocketLauncher::RocketLauncher(Entity *owner_ent); // Constructor
        RocketLauncher::~RocketLauncher(); // Destructor

        virtual int frameupdate();
        virtual void render();
        virtual void fire_shot(RESTYPE x, RESTYPE y);
    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
