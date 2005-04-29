#include"sector7.hpp"
#include"netserver.hpp"
#include "timer.hpp"

NetServer *server = NULL;
Console *console;
Entity *my_ship;

int main(int argc, char *argv[])
{
    quit = false;
    servername = "localhost";

    NetClient *client;
    std::list<Sector *> sectors;

    console = new Console();
    
    console->print_logs = 1;
    my_ship = NULL;
    int dirty=0;

    client = new NetClient(servername, DEFAULT_PORT, "netclient");
 
//    soundmgr = new SoundCore();
    
    Renderer  *renderer = new Renderer();
    Texture *no_texture = get_tex_id(TILE_NOTILE);

//    bg_particles = new EntityMgr();
//    fg_particles = new EntityMgr();
//    scoreboard = new ScoreBoard();
//    entmgr = new EntityMgr();
//    player1 = new Player();

  //  entmgr->add_entity(player1);
    
    Sector *sector = new Sector("connecting");
    sector->setup_connecting();
    sectors.push_front(sector);
    
    SDL_Event event;
    Sint32 speed = 0;
    Uint8 keys[1024];
    Uint32 framecount = 0;
    std::list< Sector * >::iterator i;
    Sector *new_sector;

    for (speed = 0; speed < 256; speed++)
        keys[speed] = SDL_RELEASED;
  
    while(!quit){
        while (SDL_PollEvent (&event) == 0 && !quit)
        {
            wait_next_frame();
            renderer->RenderFrame((*sectors.begin()));

            new_sector = client->do_frame();
            
            if(new_sector){
                sectors.push_front(new_sector);
            }

            if (my_ship){
                if (keys[SDLK_w] == SDL_PRESSED){
                    my_ship->move (0, -SHIP_SPEED);
                    dirty = 1;
                }
    
                if (keys[SDLK_a] == SDL_PRESSED){
                    my_ship->move (-SHIP_SPEED, 0);
                    dirty = 1;
                }

                if (keys[SDLK_s] == SDL_PRESSED){
                    my_ship->move (0, SHIP_SPEED);
                    dirty = 1;
                }

                if (keys[SDLK_d] == SDL_PRESSED){
                    my_ship->move (SHIP_SPEED, 0);
                    dirty = 1;
                }

                if(my_ship->texture != no_texture && dirty){
                    NetPacket *dumper = new NetPacket(sizeof(EntFull));

                    EntFull *entData = (EntFull *) &dumper->command;
                    entData->cmd = (NetCmd) htonl(INFO_ENT_FULL);
                    my_ship->deflateFull(entData);
                    client->talker->send(dumper);
                    dirty = 0;

                    delete dumper;
                }
            }
            
            if (keys[SDLK_RETURN] == SDL_PRESSED)
                quit = true;
            
            if (keys[SDLK_ESCAPE] == SDL_PRESSED)
                quit = true;
            
            for(i = sectors.begin() ; i != sectors.end(); ++i){
                (*i)->frameupdate();
            }

            framecount++;
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
    SDL_Quit();
    exit (0);
}

