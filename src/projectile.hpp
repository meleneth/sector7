#ifndef ___projectile_inc
#define ___projectile_inc 1

#include"SDL.h"
#include"entity.hpp"

class Projectile : public Entity {
    public:
        Uint16 damage;
        Entity *who_held_the_gun; // FIXME bugsource from ent going away with projectiles still active
        Uint16 lifespan;

        Projectile::Projectile(Sint16 dmg, Vector *direction, Entity *firing_party); // Constructor
        Projectile::Projectile(Projectile *source);
        Projectile::~Projectile(); // Destructor

        virtual int frameupdate(void);
        virtual int chkCollision(Entity *check);
    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
