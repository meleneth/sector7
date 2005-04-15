#ifndef ___w_scatterplasma_inc
#define ___w_scatterplasma_inc 1

#include"w_plasmacannon.hpp"

#include"SDL.h"

class ScatterPlasma : public PlasmaCannon {
    public:
        Sint32 angoffset;
        Sint32 angdir;

        // Public data members go here.
        ScatterPlasma::ScatterPlasma(Entity *owner_ent); // Constructor
        ScatterPlasma::~ScatterPlasma(); // Destructor

        virtual void fire_shot(RESTYPE x, RESTYPE y);

    private:
        // Private members go here.
    protected:
        // Protected members go here.
};

#endif
