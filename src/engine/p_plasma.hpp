#ifndef ___p_plasma_inc
#define ___p_plasma_inc 1

#include"SDL.h"
#include"projectile.hpp"

class Plasma : public Projectile {
    public:
        Plasma(Sint16 dmg, Vector *direction, Entity *firing_party); // Constructor
        ~Plasma(); // Destructor
};

#endif
