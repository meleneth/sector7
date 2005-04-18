#include "stdutil.hpp"
#include "game.hpp"
#include"map_defines.hpp"
#include"entitymgr.hpp"

#include"renderer.hpp"
#include"engine.hpp"

#include<math.h>

// Public data members go here.
Game::Game ()			// Constructor
{
    quit=0;
    framecount=0;
}

Game::~Game ()			// Destructor
{
}

int
Game::init (void)
{
//  level = new AsteroidField();
  return true;
}

int Game::run (void)
{
    SDL_Event event;
    Sint32 speed = 0;

    for (speed = 0; speed < 256; speed++)
        keys[speed] = SDL_RELEASED;

    for (;;)
    {
        while (SDL_PollEvent (&event) == 0)
        {
            if (quit == true)
                shutdown();
            handle_user_input();
            SDL_Delay (5);
            framecount++;
            entmgr->run_event();
            renderer->RenderFrame ();
            entmgr->frameupdate();
    //        level->frameupdate();
            bg_particles->frameupdate();
            fg_particles->frameupdate();
        }
        switch (event.type)
        {
            case SDL_ACTIVEEVENT:
                {
                    if (event.active.state & SDL_APPACTIVE)
                    {
                        if (event.active.gain)
                        {
                            printf ("App activated\n");
                        }
                        else
                        {
                            printf ("App iconified\n");
                        }
                    }
                }
                break;

            case SDL_QUIT:
                {
                    printf ("Quit requested, quitting.\n");
                    quit=true;
                }
                break;
            case SDL_KEYUP:
                //Keyboard handler
                //      printf("-Value: %d\n",event.key.keysym.sym);

                keys[event.key.keysym.sym] = 0;
                break;

            case SDL_KEYDOWN:
                //              printf("Value: %d\n",event.key.keysym.sym);
                keys[event.key.keysym.sym] = SDL_PRESSED;
                break;

        }

    }

}

void Game::add_sector(Sector *sector)
{
    sectors.push_front(sector);
}

void Game::handle_user_input()
{
/*
    int x, y;
    if(!player1)
        return;

    static int middle_state;
    mbuttons = SDL_GetMouseState (&x, &y);
    player1->cursor->set_from_screen_coords(x, y);

    if (mbuttons & 1)
       player1->fire ();
    
    int this_state = mbuttons & 2;
    if (this_state && !middle_state)
        player1->rotate_secondary_weapon();

    middle_state = this_state;
    
    if (mbuttons & 4)
        player1->alt_fire();
    
    if (keys[SDLK_w] == SDL_PRESSED)
        player1->MvShip (0, -SHIP_SPEED);
   
    if (keys[SDLK_a] == SDL_PRESSED)
        player1->MvShip (-SHIP_SPEED, 0);

    if (keys[SDLK_s] == SDL_PRESSED)
        player1->MvShip (0, SHIP_SPEED);

    if (keys[SDLK_d] == SDL_PRESSED)
        player1->MvShip (SHIP_SPEED, 0);
*/    
    if (keys[SDLK_ESCAPE] == SDL_PRESSED)
        quit = true;
 
}

void Game::shutdown()
{
 //   printf ("\n\nYour score was: %d\nMaximum ent_id was %d\n\n ", scoreboard->score, entmgr->ent_id);
    SDL_PumpEvents ();
    int x,y;
    mbuttons = SDL_GetMouseState (&y, &x);
    if (mbuttons != 0)
        while (mbuttons != 0)
        {
            SDL_PumpEvents ();
            mbuttons = SDL_GetMouseState (&y, &x);
        }
    SDL_Quit();
    exit (0);
}


// Private members go here.

// Protected members go here.
