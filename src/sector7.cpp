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
#include<curses.h>

NetServer *server = NULL;
Console *console;
Entity *my_ship;
ScoreBoard *scoreboard;

#define SHIP_SPEED 3

int main(int argc, char *argv[])
{
    int typing = 0;
    int msglife = 0;
    std::string input;
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
                
                if (!typing){
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

                if (scoreboard->on){
                    scoreboard->DrawNumAt(my_ship->v->x, 5, -200, -200);
                    scoreboard->DrawNumAt(my_ship->v->y, 5, -200, -184);

                    scoreboard->DrawNumAt(camera->position->x, 5, 200, -200);
                    scoreboard->DrawNumAt(camera->position->y, 5, 200, -184);
                    if (--msglife){
                        scoreboard->DrawStringAt(input, input.length(), 0, 0);
                    } else {    
                        input = "";
                    }
                }
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
                            my_ship->v->power /= 4;
                        break;
                }
                keys[event.key.keysym.sym] = 0;
                break;

            case SDL_KEYDOWN:
                if (typing){
                    switch( event.key.keysym.sym ){
                        case SDLK_RETURN:
                            if (typing = 1){
                                typing = 0;
                                msglife = 150;
                            }
                            break;
                        case SDLK_SPACE:
                            input += ' ';
                            break;
                        case SDLK_a:
                            input += 'a';
                            break;
                        case SDLK_b:
                            input += 'b';
                            break;
                        case SDLK_c:
                            input += 'c';
                            break;
                        case SDLK_d:
                            input += 'd';
                            break;
                        case SDLK_e:
                            input += 'e';
                            break;
                        case SDLK_f:
                            input += 'f';
                            break;
                        case SDLK_g:
                            input += 'g';
                            break;
                        case SDLK_h:
                            input += 'h';
                            break;
                        case SDLK_i:
                            input += 'i';
                            break;
                        case SDLK_j:
                            input += 'j';
                            break;
                        case SDLK_k:
                            input += 'k';
                            break;
                        case SDLK_l:
                            input += 'l';
                            break;
                        case SDLK_m:
                            input += 'm';
                            break;
                        case SDLK_n:
                            input += 'n';
                            break;
                        case SDLK_o:
                            input += 'o';
                            break;
                        case SDLK_p:
                            input += 'p';
                            break;
                        case SDLK_q:
                            input += 'q';
                            break;
                        case SDLK_r:
                            input += 'r';
                            break;
                        case SDLK_s:
                            input += 's';
                            break;
                        case SDLK_t:
                            input += 't';
                            break;
                        case SDLK_u:
                            input += 'u';
                            break;
                        case SDLK_v:
                            input += 'v';
                            break;
                        case SDLK_w:
                            input += 'w';
                            break;
                        case SDLK_x:
                            input += 'x';
                            break;
                        case SDLK_y:
                            input += 'y';
                            break;
                        case SDLK_z:
                            input += 'z';
                            break;
                    }
                } else {
                    switch( event.key.keysym.sym ){
                        case SDLK_SPACE:
                            if (my_ship) 
                                my_ship->v->power *= 4;
                            break;
                        case SDLK_b:
                            if(scoreboard->on){
                                scoreboard->on = false;
                                break;
                            }
                            scoreboard->on = true;
                            break;
                        case SDLK_ESCAPE:
                            quit = true;
                            break;
                        case SDLK_RETURN:
                            typing = 1;
                            break;
                    }
                    keys[event.key.keysym.sym] = SDL_PRESSED;
                    break;
                }

        }
    }
    SDL_Quit();
    exit (0);
}



