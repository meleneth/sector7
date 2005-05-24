#include<stdio.h>
#include<unistd.h>
#include"sector7.hpp"
#include"netserver.hpp"
#include"timer.hpp"
#include"vector.hpp"
#include"camera.hpp"
#include"globals.hpp"
#include"w_plasmacannon.hpp"
#include"scoreboard.hpp"
#include<sstream>

NetServer *server = NULL;
Console *console;
Entity *my_ship;
ScoreBoard *scoreboard;

#define SHIP_SPEED 3

int main(int argc, char *argv[])
{
    std::stringstream buf;
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

    Area *screensize = new Area(xres, yres);
            
    int mx, my;
    Uint8 mbuttons;
    
    quit = false;

    NetClient *client;
    std::list<Sector *> sectors;

    my_ship = NULL;

    client = new NetClient(servername, DEFAULT_PORT, nickname);
    
    renderer = new Renderer(xres, yres);
    Camera *camera = new Camera("camera1", xres, yres);
    Entity *mouse_cursor = new Entity();
    mouse_cursor->texture = get_tex_id(TILE_RETICLE);
    Texture *no_texture = get_tex_id(TILE_NOTILE);

    scoreboard = new ScoreBoard();
        
    Sector *sector = new Sector("connecting");
    sector->setup_connecting();
    camera->attach_sector(sector);
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
            if(my_ship){
                camera->follow(my_ship);
            }

            renderer->RenderFrame(camera);

            if(my_ship){

                glLoadIdentity();
                glTranslatef(mouse_cursor->v->x, mouse_cursor->v->y, 0);

                mouse_cursor->v->angle += 4;
                if (mouse_cursor->v->angle > 360)
                    mouse_cursor->v->angle = 0;

                glColor4f(0, 1, 0, .65);
                mouse_cursor->render(camera->position);
                
                if (keys[SDLK_w] == SDL_PRESSED){
                    if(my_ship->v->power < 7) my_ship->v->power += 0.1;
                }
    
                if (keys[SDLK_a] == SDL_PRESSED){
                }

                if (keys[SDLK_s] == SDL_PRESSED){
                    if(my_ship->v->power > 0) my_ship->v->power -= 0.1;
                }

                if (keys[SDLK_d] == SDL_PRESSED){
                }
                
                mbuttons = SDL_GetMouseState(&mx, &my);
                camera->set_from_screen_coords(mouse_cursor->v, mx, my);

                if(mbuttons & 1){
                    if(!(my_ship->primary->lastfire)){
                        send_net_cmd(client->talker, ENT_FIRE, 0, NULL);
                    }
                }

                my_ship->v->aim(mouse_cursor->v->x, mouse_cursor->v->y);

                if(my_ship->texture != no_texture && !(framecount % 4)){
                    NetPacket *dumper = new NetPacket(sizeof(EntFull));
                    EntFull *entData = (EntFull *) &dumper->command;
                    entData->cmd = (NetCmd) htonl(INFO_ENT_FULL);
                    my_ship->deflateFull(entData);
                    client->talker->send(dumper);

                    delete dumper;
                }

                scoreboard->DrawNumAt(floor(my_ship->v->x), 5, -200, -200);
                scoreboard->DrawNumAt(floor(my_ship->v->y), 5, -200, -184);

                scoreboard->DrawNumAt(floor(camera->position->x), 5, 200, -200);
                scoreboard->DrawNumAt(floor(camera->position->y), 5, 200, -184);

            }

            wait_next_frame();

            renderer->swap_buffers();

            new_sector = client->do_frame();
            
            if(new_sector){
                Area *inner_bound = camera->radar->actual_size;
                delete camera->radar;
                camera->radar = new Radar(new_sector->bound,  inner_bound);
                sectors.push_front(new_sector);
                camera->attach_sector(new_sector);
                if (sector){
                    camera->detach_sector(sector);
                    sector = NULL;
                }
            }
            
            for(i = sectors.begin() ; i != sectors.end(); ++i){
                (*i)->frameupdate();
            }

            framecount++;

/*            std::stringstream buf;
            buf << "CameraX: " << camera->position->x << " CameraY: " << camera->position->y;
            if(my_ship){
                buf << " ShipX: " << my_ship->v->x << " ShipY: " << my_ship->v->y;
            }
            console->log(buf.str());*/
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
                switch( event.key.keysym.sym ){
                    case SDLK_SPACE:
                        if (my_ship) 
                            my_ship->v->power = 1;
                        break;
                }
                keys[event.key.keysym.sym] = 0;
                break;

            case SDL_KEYDOWN:
                switch( event.key.keysym.sym ){
                    case SDLK_SPACE:
                        if (my_ship) 
                            my_ship->v->power = 15;
                        break;
                    case SDLK_ESCAPE:
                        quit = true;
                        break;
                    case SDLK_RETURN:
                        quit = true;
                        break;
                }
                keys[event.key.keysym.sym] = SDL_PRESSED;
                break;
        }

    }
    SDL_Quit();
    exit (0);
}



