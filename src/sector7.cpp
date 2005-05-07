#include<stdio.h>
#include<unistd.h>
#include"sector7.hpp"
#include"netserver.hpp"
#include"timer.hpp"
#include"vector.hpp"
#include"camera.hpp"
#include"globals.hpp"
#include"w_plasmacannon.hpp"

NetServer *server = NULL;
Console *console;
Entity *my_ship;

#define SHIP_SPEED 3

int main(int argc, char *argv[])
{
    std::string nickname = "netclient";
    std::string servername = "localhost";
    Uint32 xres = 1024;
    Uint32 yres = 768;

    int option_char;
    if (argc > 1)
    while ((option_char = getopt (argc, argv, "n:s:x:y:")) != EOF){
        switch (option_char){
            case 'n':
                nickname = strdup(optarg); break;
            case 's':
                servername = strdup(optarg); break;
            case 'x':
                xres = atoi (optarg); break;
            case 'y':
                yres = atoi (optarg); break;
        }
    }

    console = new Console();
    console->print_logs = 1;

    Vector *mouse_cursor = new Vector();
    Area *area = new Area(200, 200);
    Area *screensize = new Area(xres, yres);
            
    int mx, my;
    Uint8 mbuttons;
    
    quit = false;

    NetClient *client;
    std::list<Sector *> sectors;

    Camera *camera = new Camera("camera1", xres, yres);
    my_ship = NULL;

    client = new NetClient(servername, DEFAULT_PORT, nickname);
    
    renderer = new Renderer(xres, yres);
    Texture *no_texture = get_tex_id(TILE_NOTILE);
    mouse_cursor = new Vector();
    int reticle_angle = 0;

    Sector *sector = new Sector("connecting");
    camera->follow(sector->setup_connecting());
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
            renderer->RenderFrame(*(sectors.begin()));

            if(my_ship){
                camera->follow(my_ship);

                glLoadIdentity();
                glTranslatef(mouse_cursor->x, mouse_cursor->y, 0);

                reticle_angle += 4;
                if (reticle_angle > 360)
                    reticle_angle = 0;
                glRotatef(reticle_angle, 0, 0, 1);
                glColor4f(0, 1, 0, .65);
                get_tex_id(TILE_RETICLE)->DrawGLSquare(16);

            }

            wait_next_frame();

            renderer->swap_buffers();

            new_sector = client->do_frame();
            
            if(new_sector){
                sectors.push_front(new_sector);
            }

            if (my_ship){
                if (keys[SDLK_w] == SDL_PRESSED){
                    if(my_ship->v->power < 7) my_ship->v->power += 0.1;
                }
    
                if (keys[SDLK_a] == SDL_PRESSED){
                }

                if (keys[SDLK_s] == SDL_PRESSED){
                    if(my_ship->v->power) my_ship->v->power -= 0.1;
                }

                if (keys[SDLK_d] == SDL_PRESSED){
                }

              
                mbuttons = SDL_GetMouseState(&mx, &my);
                mouse_cursor->set_from_screen_coords(mx, my, xres, yres);

                if(mbuttons & 1){
                   send_net_cmd(client->talker, ENT_FIRE, 0, NULL);
                }

                my_ship->v->aim(mouse_cursor->x, mouse_cursor->y);

                if(my_ship->texture != no_texture && !(framecount % 4)){
                    NetPacket *dumper = new NetPacket(sizeof(EntFull));
                    EntFull *entData = (EntFull *) &dumper->command;
                    entData->cmd = (NetCmd) htonl(INFO_ENT_FULL);
                    my_ship->deflateFull(entData);
                    client->talker->send(dumper);

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



