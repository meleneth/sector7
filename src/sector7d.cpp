#include<stdio.h>
#include<signal.h>
#include<ncurses.h>

#include"texture.hpp"
#include"console.hpp"
#include"netclient.hpp"
#include"netserver.hpp"
#include"sector.hpp"
#include"entitymgr.hpp"
#include"globals.hpp"
#include"timer.hpp"

#include"SDL.h"

void do_init(void);
static void finish(int sig);

extern Uint32 xres;
extern Uint32 yres;

Console *console;

NetClient *client;
NetServer *server;

EntityMgr *entmgr;
Entity *my_ship;

std::string nickname;
std::string servername;

int main(int argc, char *argv[])
{
    signal(SIGINT, finish);
    initscr();
    keypad(stdscr, TRUE);
    nonl();
    cbreak();
    noecho();
    nodelay(stdscr, 1);
    server = NULL;
    console = new Console(COLS, LINES);
    load_textures(1);
    my_ship = NULL;
    std::list<Sector *> sectors;

    server = new NetServer(DEFAULT_PORT, "initialD");
    nickname = "SERVER";
    servername = "localhost";

    std::string input("");

    std::list<Sector *>::iterator i;

    server->setup_master();
    sectors.push_front(server);
    
    while(1){
        // Select loop here
        wait_next_frame();

        int key = getch();
        if(key != ERR){
            if(key == 13){
                std::string line;
                line = "> " + input;
                console->log(line);
                input = "";
            }else {
                input += (char)key;
            }
        }
        server->do_frame();

        for(i = sectors.begin() ; i != sectors.end(); ++i){
            (*i)->frameupdate_with_collisions();
        }
        console->render();
        mvaddstr(LINES-1, 0, input.c_str());
        refresh();
    }

    finish(0);
}


static void finish(int sig)
{
    endwin();
    delete server;
    delete console;
    exit(0);
}


