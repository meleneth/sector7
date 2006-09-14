/*Stop multiple inclusion */
#ifndef ___physics_inc
#define ___physics_inc 1


#include"SDL.h"

class Physics {
    public:
        Uint16 topspeed;
        Uint16 accelerationrate;
        Sint16 momentum;
        Sint16 turnrate;

        // Public data members go here.
        Physics(); // Constructor
        ~Physics(); // Destructor
        Sint16 howfast(int accelerating);
        Sint16 getturnrate();
    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
