#ifndef ___level_inc
#define ___level_inc 1

#include"SDL.h"

class Level {
    public:
        Uint32 framecount;

        Level::Level(void); // Constructor
        Level::~Level(); // Destructor

        virtual void frameupdate(void);
    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
