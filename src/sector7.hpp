#ifndef SECTOR7_HEADER
#define SECTOR7_HEADER 1

#include"stdutil.hpp"
#include"renderer.hpp"
#include"game.hpp"
#include"player.hpp"
#include"console.hpp"
#include"particles.hpp"
#include"entitymgr.hpp"
//#include"scoreboard.hpp"
//#include"soundcore.hpp"

//SoundCore *soundmgr = NULL;
Renderer *renderer = NULL;
Game *game = NULL;
Player *player1 = NULL;
Console *sysconsole = NULL;
EntityMgr *bg_particles = NULL;
EntityMgr *fg_particles = NULL;
EntityMgr *entmgr = NULL;
//ScoreBoard *scoreboard = NULL;

Uint32 quit = false;

char *servername = NULL;

#endif
