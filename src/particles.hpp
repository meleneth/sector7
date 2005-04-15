/*Stop multiple inclusion */
#ifndef ___particles_inc
#define ___particles_inc 1

#include"texture.hpp"
#include"vector.hpp"
#include"SDL.h"


class Particle {
    public:
        Vector *v;
        double xv, yv;
        Texture *t;
        Uint16 size;
        Uint32 lifespan;
        float red, green, blue, alpha;


        Particle::Particle(); // Constructor
        Particle::~Particle(); // Destructor

};

class ParticleSystem {
    public:
        std::list < Particle * > particles;

        // Public data members go here.
        ParticleSystem::ParticleSystem(); // Constructor
        ParticleSystem::~ParticleSystem(); // Destructor

        void render(void);
        void frameupdate(void);

    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
