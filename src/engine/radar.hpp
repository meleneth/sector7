#ifndef ___radar_inc
#define ___radar_inc 1

#include"SDL.h"
#include"area.hpp"
#include"texture.hpp"

class Radar {
    public:
        // Public data members go here.
        Radar(Area *actual_size, Area *rendered_size); // Constructor
        ~Radar(); // Destructor

        void blip(Vector *p);

        Area *actual_size;
        Area *rendered_size;
        Texture *texture;
    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

#endif
