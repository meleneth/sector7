#ifndef ___game_inc
#define ___game_inc 1

#define SHIP_SPEED 5

#include"SDL.h"
#include"sector.hpp"
#include<list>

class Game {
    public:
        // Public data members go here.
        Game::Game(); // Constructor
        Game::~Game(); // Destructor
        int init(void);
        int run(void);
        void add_sector(Sector *sector);
        void shutdown(void);
        void handle_user_input(void);
        void handle_event(SDL_Event event);

        Uint32 framecount;
    private:
        Uint8 keys[1024];
        Uint8 mbuttons;
        Uint16 quit;

        std::list< Sector * > sectors;

    protected:
        // Protected members go here.
};

#endif
