#include"sector7d.hpp"
#include"globals.hpp"
#include"sector.hpp"

Console *console;

int main(int argc, char *argv[])
{
    quit = false;
    servername = "localhost";

    console = new Console();
    
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

