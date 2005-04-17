#include"sector7d.hpp"
#include"globals.hpp"

Console *console;

int main(int argc, char *argv[])
{
    quit = false;
    servername = "localhost";

    console = new Console();
    
//    soundmgr = new SoundCore();
    renderer = new Renderer();
    bg_particles = new EntityMgr();
    fg_particles = new EntityMgr();
//    scoreboard = new ScoreBoard();
    entmgr = new EntityMgr();
    player1 = new Player();

    entmgr->add_entity(player1);

    game = new Game();
    game->init();
    game->run();
}

