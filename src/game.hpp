#ifndef ___game_inc
#define ___game_inc 1


#include"SDL.h"

#define SHIP_SPEED 3


class Game {
    public:
        // Public data members go here.
        Game::Game(); // Constructor
        Game::~Game(); // Destructor
        int init(void);
        int run(void);
        void shutdown(void);
        void handle_user_input(void);

        Uint32 framecount;
    private:
        Uint8 keys[1024];
        Uint8 mbuttons;
        Uint16 quit;

    protected:
        // Protected members go here.
};

#endif
