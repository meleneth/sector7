#include<stdio.h>
#include<signal.h>
#include<ncurses.h>

#include"console.hpp"
#include"netclient.hpp"
#include"netserver.hpp"

#include"SDL.h"

void do_init(void);
static void finish(int sig);

#define DEFAULT_PORT 6565

Console *console;
NetClient *client;
NetServer *server;

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

    if(argc == 1){
        server = new NetServer(DEFAULT_PORT);
        nickname = "SERVER";
        servername = "localhost";
    }else if(argc == 3){
        nickname = strdup(argv[1]);
        servername = strdup(argv[2]);
    }else{
        printf("Usage: ncu nick servername\n");
        printf("Running with no args will run in server mode\n\n");
    }

    client = new NetClient(servername, DEFAULT_PORT, nickname);

    do_init();

    std::string input("");

    while(1){
        // Select loop here

        SDL_Delay(10);

        int key = getch();
        if(key != ERR){
            if(key == 13){
                std::string line;
                line = "> " + input;
                console->log(line);
                client->send_line(input);
                input = "";
            }else {
                input += (char)key;
            }
        }
        client->do_frame();
        if(server){
            server->do_frame();
        }
        console->render();
        mvaddstr(LINES-1, 0, input.c_str());
        refresh();
    }

    finish(0);
}

void do_init(void)
{
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

