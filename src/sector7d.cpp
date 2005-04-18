#include"sector7d.hpp"
#include"globals.hpp"
#include"sector.hpp"

#include<curses.h>
#include<stdio.h>
#include<signal.h>
#include<ncurses.h>

Console *console;

void init_ncurses(void);
static void finish(int sig);

int main(int argc, char *argv[])
{
    quit = false;
    servername = "localhost";
    init_ncurses();
    console = new Console(COLS, LINES);
    
//    soundmgr = new SoundCore();
    renderer = NULL;
    bg_particles = NULL;
    fg_particles = NULL;
//    scoreboard = new ScoreBoard();
    
    Sector *sector = new Sector("master");
    sector->setup_master();

    game = new Game();
    game->init();
    game->add_sector(sector);
    game->run();
}

void init_ncurses(void)
{
    signal(SIGINT, finish);
    initscr();
    keypad(stdscr, TRUE);
    nonl();
    cbreak();
    noecho();
    nodelay(stdscr, 1);
}


static void finish(int sig)
{
    delete console;
    endwin();
    printf("\n\n\nBomb out!\n\n\n");
    exit(0);
}


