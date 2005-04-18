#include<stdio.h>
#include<signal.h>
#include<ncurses.h>

#include"console.hpp"
#include"netclient.hpp"
#include"netserver.hpp"
#include"sector.hpp"
#include"entitymgr.hpp"

#include"SDL.h"

void do_init(void);
static void finish(int sig);

#define DEFAULT_PORT 6565

Console *console;

NetClient *client;
NetServer *server;

EntityMgr *entmgr;

std::list< Sector * > sectors;

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

    server = new NetServer(DEFAULT_PORT);
    nickname = "SERVER";
    servername = "localhost";

    std::string input("");

    std::list<Sector *>::iterator i;

    while(1){
        // Select loop here

        SDL_Delay(10);

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
        if(server){
            server->do_frame();
        }

        for(i = sectors.begin() ; i != sectors.end(); ++i){
            (*i)->frameupdate();
        }
        console->render();
        mvaddstr(LINES-1, 0, input.c_str());
        refresh();
    }

    finish(0);
}


static void finish(int sig)
{
    delete console;
    if(server)
        delete server;
    delete client;
    endwin();
    printf("\n\n\nBomb out!\n\n\n");
    exit(0);
}

