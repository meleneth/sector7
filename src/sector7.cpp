#include"sector7.hpp"
#include"netserver.hpp"
#include"timer.hpp"
#include"vector.hpp"

NetServer *server = NULL;
Console *console;
Entity *my_ship;

#define SHIP_SPEED 3

int main(int argc, char *argv[])
{
    std::string nickname;
    std::string servername;
    Vector *mouse_cursor = new Vector();

    int mx, my;
    Uint8 mbuttons;
    
    if(argc == 1){
        nickname = "netclient";
        servername = "localhost";
    }else if(argc == 3){
        nickname = strdup(argv[1]);
        servername = strdup(argv[2]);
    }else{
        printf("Usage: s7 [nick servername]\n");
        exit(0);
    }
    quit = false;

    NetClient *client;
    std::list<Sector *> sectors;

    console = new Console();
    
    console->print_logs = 1;
    my_ship = NULL;
    int dirty=0;

    client = new NetClient(servername, DEFAULT_PORT, nickname);
    
    Renderer  *renderer = new Renderer();
    Texture *no_texture = get_tex_id(TILE_NOTILE);
    mouse_cursor = new Vector();
    int reticle_angle = 0;

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

            if(my_ship){
                glLoadIdentity();
                glTranslatef(mouse_cursor->x, mouse_cursor->y, 0);

                reticle_angle += 4;
                if (reticle_angle > 360)
                    reticle_angle = 0;
                glRotatef(reticle_angle, 0, 0, 1);
                glColor4f(0, 1, 0, .65);
                get_tex_id(TILE_RETICLE)->DrawGLSquare(16);
            }

            renderer->swap_buffers();

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

                mbuttons = SDL_GetMouseState(&mx, &my);
                if(mbuttons & 1){
                    my_ship->log_info();
                }
                mouse_cursor->set_from_screen_coords(mx, my);

                my_ship->v->aim(mouse_cursor->x, mouse_cursor->y);
                my_ship->v->angle -= 90;

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
                if (event.active.state & SDL_APPACTIVE)
                    if (event.active.gain)
                        printf ("App activated\n");
                    else
                        printf ("App iconified\n");
                break;

            case SDL_QUIT:
                printf ("Quit requested, quitting.\n");
                quit=true;
                break;
                
            case SDL_KEYUP:
                keys[event.key.keysym.sym] = 0;
                break;

            case SDL_KEYDOWN:
                keys[event.key.keysym.sym] = SDL_PRESSED;
                break;

        }

    }
    SDL_Quit();
    exit (0);
}

