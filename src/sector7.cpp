#include"sector7.hpp"

Console *console;

int main(int argc, char *argv[])
{
    quit = false;
    servername = "localhost";

    NetClient *client;

    sysconsole = new Console();

    client = new NetClient(servername, DEFAULT_PORT, "netclient");
    
	
	
//    soundmgr = new SoundCore();
//    renderer = new Renderer();
//    bg_particles = new EntityMgr();
//    fg_particles = new EntityMgr();
//    scoreboard = new ScoreBoard();
//    entmgr = new EntityMgr();
//    player1 = new Player();

  //  entmgr->add_entity(player1);

}

