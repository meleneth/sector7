#include"sector7d.hpp"

int main(int argc, char *argv[])
{
    quit = false;
    servername = "localhost";

    sysconsole = new Console();
    
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

