#ifndef ___p_plasma_inc
#define ___p_plasma_inc 1

#include"SDL.h"
#include"projectile.hpp"

class Plasma : public Projectile {
    public:
// Public data members go here.
        Plasma::Plasma(Sint16 dmg, Vector *direction, Entity *firing_party); // Constructor
        Plasma::~Plasma(); // Destructor
    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
