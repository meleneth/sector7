#include"sector7.hpp"

Console *console;

int main(int argc, char *argv[])
{
    quit = false;
    servername = "localhost";

    NetClient *client;

    console = new Console();
    
    console->print_logs = 1;

    client = new NetClient(servername, DEFAULT_PORT, "netclient");
    Sector *sector = new Sector("connecting");
    sector->setup_connecting();
    
//    soundmgr = new SoundCore();
    Renderer  *renderer = new Renderer();
//    bg_particles = new EntityMgr();
//    fg_particles = new EntityMgr();
//    scoreboard = new ScoreBoard();
//    entmgr = new EntityMgr();
//    player1 = new Player();

  //  entmgr->add_entity(player1);
    while(!quit){
        renderer->RenderFrame(sector);
    }
}

