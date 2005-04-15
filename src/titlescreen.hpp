/*Stop multiple inclusion */
#ifndef ___titlescreen_inc
#define ___titlescreen_inc 1


#include"SDL.h"
#include"entity.hpp"

class TitleScreen :public Entity{
    public:
        // Public data members go here.
        TitleScreen::TitleScreen(); // Constructor
        TitleScreen::~TitleScreen(); // Destructor

        virtual int chkCollision(Uint16 ent_type, Sint16 pointx, Sint16 pointy, Sint16 mysize);
        virtual int chkDeath(void);
        virtual void render();

    private:
        // Private members go here.

    protected:
        // Protected members go here.
};

#endif
